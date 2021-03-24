#ifndef CLASSIC_PHASE_HPP
#define CLASSIC_PHASE_HPP

#include <libchess/position.hpp>
#include "../../score.hpp"

namespace classic {

[[nodiscard]] int phase(const libchess::Position &pos, const Score &score) noexcept;

}  // namespace classic

#endif
