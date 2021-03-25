#ifndef SEARCH_RANDOM_HPP
#define SEARCH_RANDOM_HPP

#include <libchess/move.hpp>
#include <libchess/position.hpp>
#include "../search.hpp"

namespace rando {

search_return search(libchess::Position pos, const info_printer &info) {
    const auto moves = pos.legal_moves();

    if (!moves.empty()) {
        return {moves.at(rand() % moves.size()), {}};
    }

    return {};
}

}  // namespace rando

#endif
