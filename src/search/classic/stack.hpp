#ifndef CLASSIC_SEARCH_STACK_HPP
#define CLASSIC_SEARCH_STACK_HPP

#include "../pv.hpp"

namespace classic {

struct Stack {
    int ply;
    bool nullmove;
    PV pv;
};

}  // namespace classic

#endif
