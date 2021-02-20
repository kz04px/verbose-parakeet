#ifndef CLASSIC_SEARCH_HPP
#define CLASSIC_SEARCH_HPP

#include <cstdint>
#include <functional>
#include <libchess/position.hpp>
#include "../pv.hpp"

namespace classic {

using info_printer = std::function<void(int depth, int score, std::uint64_t nodes, int time, const PV &pv)>;

std::pair<libchess::Move, libchess::Move> search(libchess::Position pos);
std::pair<libchess::Move, libchess::Move> search(libchess::Position pos, const info_printer info);

}  // namespace classic

#endif
