#ifndef CLASSIC_IS_ENDGAME_HPP
#define CLASSIC_IS_ENDGAME_HPP

#include <libchess/position.hpp>

namespace classic {

[[nodiscard]] inline bool is_endgame(const libchess::Position &pos) {
    const auto piece_mask = pos.occupancy(libchess::Piece::Knight) | pos.occupancy(libchess::Piece::Bishop) |
                            pos.occupancy(libchess::Piece::Rook) | pos.occupancy(libchess::Piece::Queen);
    return (piece_mask & pos.occupancy(pos.turn())).count() <= 2;
}

}  // namespace classic

#endif
