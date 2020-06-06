#include "eval.hpp"

int eval(const libchess::Position &pos) {
    const auto us = pos.turn();
    const auto them = !us;

    int score = 0;

    score += 100 * pos.pieces(us, libchess::Piece::Pawn).count();
    score += 300 * pos.pieces(us, libchess::Piece::Knight).count();
    score += 300 * pos.pieces(us, libchess::Piece::Bishop).count();
    score += 500 * pos.pieces(us, libchess::Piece::Rook).count();
    score += 900 * pos.pieces(us, libchess::Piece::Queen).count();

    score -= 100 * pos.pieces(them, libchess::Piece::Pawn).count();
    score -= 300 * pos.pieces(them, libchess::Piece::Knight).count();
    score -= 300 * pos.pieces(them, libchess::Piece::Bishop).count();
    score -= 500 * pos.pieces(them, libchess::Piece::Rook).count();
    score -= 900 * pos.pieces(them, libchess::Piece::Queen).count();

    return score;
}
