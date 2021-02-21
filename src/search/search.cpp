#include "search.hpp"

search_type search = [](libchess::Position pos, const info_printer info) -> search_return { return {}; };

std::function<int(const libchess::Position &pos)> eval = [](const libchess::Position &pos) { return 0; };
