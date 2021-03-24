#ifndef CLASSIC_QSEARCH_HPP
#define CLASSIC_QSEARCH_HPP

#include <libchess/position.hpp>

namespace classic {

[[nodiscard]] int qsearch(libchess::Position &pos, int alpha, const int beta);

}  // namespace classic

#endif
