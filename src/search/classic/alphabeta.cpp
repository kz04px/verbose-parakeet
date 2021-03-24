#include "alphabeta.hpp"
#include <cassert>
#include <limits>
#include "../controller.hpp"
#include "eval/eval.hpp"

namespace classic {

int alphabeta(libchess::Position &pos, Stack *ss, int alpha, const int beta, int depth) {
    assert(-mate_score <= alpha);
    assert(alpha < beta);
    assert(beta <= mate_score);

    ss->pv.clear();
    const auto in_check = pos.in_check();

    if (in_check) {
        depth++;
    }

    if (pos.threefold()) {
        return 0;
    }

    if (pos.fiftymoves()) {
        // Checkmate takes priority over the fifty move rule
        if (in_check) {
            return pos.legal_moves().size() == 0 ? -mate_score + ss->ply : 0;
        }
        return 0;
    }

    if (depth <= 0) {
        return eval(pos);
    }

    if (controller.should_stop()) {
        return 0;
    }

    const auto moves = pos.legal_moves();

    if (moves.empty()) {
        // Checkmate
        if (in_check) {
            return -mate_score + ss->ply;
        }
        // Stalemate
        else {
            return 0;
        }
    }

    auto best_score = std::numeric_limits<int>::min();

    for (const auto &move : moves) {
        controller.increment_nodes();

        pos.makemove(move);
        const auto score = -alphabeta(pos, ss + 1, -beta, -alpha, depth - 1);
        pos.undomove();

        if (score > best_score) {
            best_score = score;
            ss->pv.clear();
            ss->pv.push_back(move);
            for (const auto &move : (ss + 1)->pv) {
                ss->pv.push_back(move);
            }
        }

        if (score > alpha) {
            alpha = score;

            if (score > beta) {
                break;
            }
        }
    }

    assert(best_score > std::numeric_limits<int>::min());

    return alpha;
}

}  // namespace classic
