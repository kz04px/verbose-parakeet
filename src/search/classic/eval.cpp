#include "eval.hpp"
#include <array>
#include "../score.hpp"
#include "pst.hpp"

namespace classic {

constexpr Score piece_values[] = {
    {100, 100},
    {300, 300},
    {300, 300},
    {500, 500},
    {900, 900},
    {1000000, 1000000},
};

template <libchess::Side side>
[[nodiscard]] Score eval_side(const libchess::Position &pos) {
    Score score;

    for (const auto p : libchess::pieces) {
        // Piece values
        score += piece_values[p] * pos.pieces(side, p).count();

        for (const auto sq : pos.pieces(side, p)) {
            // Piece square tables
            score += pst_value<side>(p, sq);
        }
    }

    return score;
}

int eval(const libchess::Position &pos) {
    Score score;
    score += eval_side<libchess::Side::White>(pos);
    score -= eval_side<libchess::Side::Black>(pos);
    if (pos.turn() == libchess::Side::Black) {
        return -score.phase(pos);
    }
    return score.phase(pos);
}

}  // namespace classic
