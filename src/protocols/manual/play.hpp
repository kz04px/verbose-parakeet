#ifndef MANUAL_PLAY_HPP
#define MANUAL_PLAY_HPP

#include <libchess/side.hpp>
#include <string>

namespace manual {

void play(const std::string &fen, const libchess::Side human);

}  // namespace manual

#endif
