#ifndef CLASSIC_ALPHABETA_HPP
#define CLASSIC_ALPHABETA_HPP

#include <libchess/position.hpp>
#include "stack.hpp"

namespace classic {

constexpr int mate_score = 10000;

int alphabeta(libchess::Position &pos, Stack *ss, const int alpha, const int beta, const int depth);

}  // namespace classic

#endif
