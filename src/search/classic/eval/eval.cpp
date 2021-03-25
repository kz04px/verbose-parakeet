#include "eval.hpp"
#include <array>
#include "../../score.hpp"
#include "king_safety.hpp"
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

constexpr Score rook_open_file = {25, 25};
constexpr Score turn_bonus = Score{10, 10};
constexpr Score passed_pawn_value[8] = {{0, 0}, {5, 10}, {5, 10}, {7, 15}, {12, 25}, {20, 40}, {30, 60}, {0, 0}};

template <libchess::Side side>
[[nodiscard]] Score eval_side(const libchess::Position &pos) {
    Score score;

    // King safety
    score += king_safety<side>(pos);

    // Passed pawns
    for (const auto sq : pos.passed_pawns(side)) {
        score += passed_pawn_value[sq.rank()];
    }

    // For each file
    for (int i = 0; i < 8; ++i) {
        const auto file = libchess::bitboards::files[i];
        const auto pawns = pos.occupancy(libchess::Piece::Pawn) & file;
        const auto our_rooks = pos.pieces(side, libchess::Piece::Rook) & file;

        // Rooks on open files
        if (!pawns && our_rooks) {
            score += rook_open_file;
        }
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
