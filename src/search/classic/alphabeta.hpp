#ifndef CLASSIC_ALPHABETA_HPP
#define CLASSIC_ALPHABETA_HPP

#include <libchess/position.hpp>
#include "stack.hpp"

constexpr int mate_score = 10000;

int alphabeta(libchess::Position &pos, Stack *ss, const int alpha, const int beta, const int depth);

#endif
