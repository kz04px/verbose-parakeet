#include <iostream>
#include "extensions.hpp"

namespace uci::extension {

void display(const libchess::Position &pos) {
    std::cout << pos << std::endl;
}

}  // namespace uci::extension
