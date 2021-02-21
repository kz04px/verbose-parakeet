#ifndef SEARCH_GREEDY_HPP
#define SEARCH_GREEDY_HPP

#include <libchess/move.hpp>
#include <libchess/position.hpp>
#include "../search.hpp"

namespace greedy {

search_return search(libchess::Position pos, const info_printer info);

}  // namespace greedy

#endif
