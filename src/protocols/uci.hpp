#ifndef UCI_HPP
#define UCI_HPP

#include <libchess/position.hpp>
#include <sstream>

namespace uci {

void listen();

void uci();
void isready();
void ucinewgame(libchess::Position &pos);
void position(libchess::Position &pos, std::stringstream &ss);
void moves(libchess::Position &pos, std::stringstream &ss);
void go(libchess::Position &pos, std::stringstream &ss);
void setoption(std::stringstream &ss);

}  // namespace uci

#endif
