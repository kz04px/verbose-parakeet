#ifndef UCI_EXTENSIONS_HPP
#define UCI_EXTENSIONS_HPP

#include <libchess/position.hpp>
#include <sstream>

namespace uci::extension {

void perft(libchess::Position &pos, std::stringstream &ss);
void split(libchess::Position &pos, std::stringstream &ss);
void display(const libchess::Position &pos);
void eval(const libchess::Position &pos);

}  // namespace uci::extension

#endif
