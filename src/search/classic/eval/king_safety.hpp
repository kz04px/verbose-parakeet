#ifndef CLASSIC_EVAL_KING_SAFETY_HPP
#define CLASSIC_EVAL_KING_SAFETY_HPP

#include <libchess/position.hpp>
#include "../../score.hpp"

namespace classic {

template <libchess::Side side>
[[nodiscard]] constexpr libchess::Bitboard shield(const libchess::Square sq) {
    auto bb = libchess::Bitboard(sq);
    if constexpr (side == libchess::Side::White) {
        bb = bb.north();
        bb |= bb.north();
    } else {
        bb = bb.south();
        bb |= bb.south();
    }
    bb |= bb.east();
    bb |= bb.west();
    return bb;
}

template <libchess::Side side>
[[nodiscard]] Score king_safety(const libchess::Position &pos) {
    const auto bb = pos.pieces(side, libchess::Piece::King);
    const auto sq = bb.lsbll();
    const auto pawns = shield<side>(sq) & pos.pieces(side, libchess::Piece::Pawn);
    return Score{15, 0} * pawns.count();
}

static_assert(shield<libchess::Side::White>(libchess::squares::G1) == libchess::Bitboard(0xe0e000));
static_assert(shield<libchess::Side::Black>(libchess::squares::G8) == libchess::Bitboard(0xe0e00000000000));

}  // namespace classic

#endif
