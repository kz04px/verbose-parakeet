#include "display.hpp"
#include <iostream>
#include <libchess/position.hpp>

namespace manual {

void display(const libchess::Position &pos, const bool flip) {
    std::cout << pos << std::endl;
}

}  // namespace manual
