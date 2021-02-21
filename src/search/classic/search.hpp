#ifndef CLASSIC_SEARCH_HPP
#define CLASSIC_SEARCH_HPP

#include <libchess/move.hpp>
#include <libchess/position.hpp>
#include "../search.hpp"

namespace classic {

search_return search(libchess::Position pos, const info_printer info);

}  // namespace classic

#endif
