#include <iostream>
#include "../uci.hpp"
#include "extensions.hpp"

namespace uci::extension {

void eval(const libchess::Position &pos) {
    const auto score = eval_func(pos);
    std::cout << "info string eval " << score << std::endl;
}

}  // namespace uci::extension
