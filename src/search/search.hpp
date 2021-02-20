#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <cstdint>
#include <functional>
#include <libchess/move.hpp>
#include "pv.hpp"

using info_printer = std::function<void(int depth, int score, std::uint64_t nodes, int time, const PV &pv)>;
using search_return = std::pair<libchess::Move, libchess::Move>;
using search_type = std::function<search_return(libchess::Position pos, const info_printer info)>;

extern search_type search;

#endif
