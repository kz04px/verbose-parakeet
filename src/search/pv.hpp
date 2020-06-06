#ifndef SEARCH_PV_HPP
#define SEARCH_PV_HPP

#include <libchess/position.hpp>
#include <vector>

using PV = std::vector<libchess::Move>;

[[nodiscard]] bool legal_pv(libchess::Position &pos, const PV &pv);

#endif
