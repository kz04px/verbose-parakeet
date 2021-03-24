#ifndef CLASSIC_EVAL_HPP
#define CLASSIC_EVAL_HPP

#include <libchess/position.hpp>

namespace classic {

[[nodiscard]] int eval(const libchess::Position &pos);

}  // namespace classic

#endif
