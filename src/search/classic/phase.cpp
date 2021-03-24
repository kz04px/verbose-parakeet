#include "phase.hpp"

namespace classic {

[[nodiscard]] int phase(const libchess::Position &pos, const Score &score) noexcept {
    const int num_knights = pos.occupancy(libchess::Piece::Knight).count();
    const int num_bishops = pos.occupancy(libchess::Piece::Bishop).count();
    const int num_rooks = pos.occupancy(libchess::Piece::Rook).count();
    const int num_queens = pos.occupancy(libchess::Piece::Queen).count();
    const int total_phase = 24;
    int phase = total_phase - num_knights - num_bishops - 2 * num_rooks - 4 * num_queens;
    phase = (phase * 256 + (total_phase / 2)) / total_phase;
    return ((score.mg() * (256 - phase)) + (score.eg() * phase)) / 256;
}

}  // namespace classic
