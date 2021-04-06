#include "alphabeta.hpp"
#include <cassert>
#include <limits>
#include "../controller.hpp"
#include "is_endgame.hpp"
#include "qsearch.hpp"

namespace classic {

int alphabeta(libchess::Position &pos, Stack *ss, int alpha, const int beta, int depth) {
    assert(-mate_score <= alpha);
    assert(alpha < beta);
    assert(beta <= mate_score);

    ss->pv.clear();
    const auto in_check = pos.in_check();
    const auto pvnode = beta - alpha > 1;
    const auto root = ss->ply == 0;

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
        return qsearch(pos, alpha, beta);
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

    // Null move pruning
    if (ss->nullmove && !pvnode && !root && depth > 2 && !in_check && !is_endgame(pos)) {
        constexpr int R = 2;

        pos.makenull();
        (ss + 1)->nullmove = false;
        const int score = -alphabeta(pos, ss + 1, -beta, -beta + 1, depth - 1 - R);
        pos.undonull();
        (ss + 1)->nullmove = true;

        if (score >= beta) {
            return score;
        }
    }

    auto best_score = std::numeric_limits<int>::min();

    for (const auto &move : moves) {
    for (auto i = 0; i < moves.size(); ++i) {
        controller.increment_nodes();

        pos.makemove(moves[i]);

        int score = 0;

        if (i == 0) {
            score = -alphabeta(pos, ss + 1, -beta, -alpha, depth - 1);
        } else {
            score = -alphabeta(pos, ss + 1, -alpha - 1, -alpha, depth - 1);
            if (alpha < score && score < beta) {
                score = -alphabeta(pos, ss + 1, -beta, -score, depth - 1);
            }
        }

        pos.undomove();

        if (score > best_score) {
            best_score = score;
            ss->pv.clear();
            ss->pv.push_back(moves[i]);
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
