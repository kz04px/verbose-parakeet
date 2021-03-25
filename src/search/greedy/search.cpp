#include "search.hpp"
#include <limits>
#include <vector>
#include "../controller.hpp"
#include "../pv.hpp"
#include "../search.hpp"
#include "eval.hpp"

namespace greedy {

search_return search(libchess::Position pos, const info_printer &info) {
    int best_score = std::numeric_limits<int>::lowest();
    std::vector<libchess::Move> best_moves;
    const auto moves = pos.legal_moves();

    // No legal moves
    if (moves.empty()) {
        return {};
    }

    for (const auto &move : moves) {
        pos.makemove(move);

        const int score = -eval(pos);

        if (score > best_score) {
            best_moves.clear();
            best_moves.push_back(move);
            best_score = score;
        } else if (score == best_score) {
            best_moves.push_back(move);
        }

        pos.undomove();
    }

    assert(!best_moves.empty());
    assert(best_moves.size() <= moves.size());
    assert(best_score > std::numeric_limits<int>::lowest());

    const auto best_move = best_moves.at(rand() % best_moves.size());

    assert(best_move);
    assert(pos.is_legal(best_move));

    info(1, best_score, moves.size(), controller.time_elapsed().count(), PV{best_move});

    return {best_move, {}};
}

}  // namespace greedy
