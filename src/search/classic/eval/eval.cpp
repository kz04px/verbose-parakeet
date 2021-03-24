#include "eval.hpp"
#include <array>
#include "../../score.hpp"
#include "phase.hpp"
#include "pst.hpp"

namespace classic {

constexpr Score piece_values[] = {
    {100, 100},
    {320, 320},
    {330, 330},
    {500, 500},
    {900, 900},
    {1000000, 1000000},
};

constexpr Score turn_bonus = Score{10, 10};
constexpr Score passed_pawn_value[8] = {{0, 0}, {5, 10}, {5, 10}, {7, 15}, {12, 25}, {20, 40}, {30, 60}, {0, 0}};

template <libchess::Side side>
[[nodiscard]] Score eval_side(const libchess::Position &pos) {
    Score score;

    // Passed pawns
    for (const auto sq : pos.passed_pawns(side)) {
        score += passed_pawn_value[sq.rank()];
    }

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

[[nodiscard]] int eval(const libchess::Position &pos) {
    Score score;
    score += eval_side<libchess::Side::White>(pos);
    score -= eval_side<libchess::Side::Black>(pos);
    score += turn_bonus;
    const int phased_score = phase(pos, score);
    return pos.turn() == libchess::Side::White ? phased_score : -phased_score;
}

}  // namespace classic
