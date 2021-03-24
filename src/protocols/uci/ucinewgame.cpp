#include "uci.hpp"

namespace uci {

void ucinewgame(libchess::Position &pos) {
    pos.set_fen("startpos");
}

}  // namespace uci
