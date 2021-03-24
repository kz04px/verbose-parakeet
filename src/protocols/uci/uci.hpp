#ifndef UCI_HPP
#define UCI_HPP

#include <libchess/position.hpp>
#include <sstream>
#include "../../search/search.hpp"

namespace uci {

extern search_type search_func;
extern std::function<int(const libchess::Position &pos)> eval_func;

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
