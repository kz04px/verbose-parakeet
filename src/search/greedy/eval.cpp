#include "eval.hpp"

namespace greedy {

static constexpr int piece_values[] = {100, 300, 325, 500, 900, 1000000};

int eval(const libchess::Position &pos) {
    int score = 0;

    // Draws
    if (pos.fiftymoves() || pos.threefold()) {
        if (pos.in_check() && pos.legal_moves().empty()) {
            return -1000000;
        } else {
            return 0;
        }
    }

    // Checkmates
    if (pos.in_check() && pos.legal_moves().empty()) {
        return -1000000;
    }

    // Stalemate
    if (pos.legal_moves().empty()) {
        return 0;
    }

    // White
    for (const auto p : libchess::pieces) {
        const int count = pos.pieces(libchess::Side::White, p).count();
        score += count * piece_values[static_cast<int>(p)];
    }

    // Black
    for (const auto p : libchess::pieces) {
        const int count = pos.pieces(libchess::Side::Black, p).count();
        score -= count * piece_values[static_cast<int>(p)];
    }

    return pos.turn() == libchess::Side::White ? score : -score;
}

}  // namespace greedy
