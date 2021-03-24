#include "listen.hpp"
#include <iostream>
#include <libchess/position.hpp>
#include <string>
#include "play.hpp"

namespace manual {

void listen() {
    while (true) {
        std::cout << "Commands:\n";
        std::cout << "- play\n";
        std::cout << "- quit\n";
        std::cout << "\n";

        std::string word;
        std::cin >> word;

        if (word == "play") {
            std::cout << "Colour? w/b\n";
            std::cin >> word;
            play("startpos", word == "w" ? libchess::Side::White : libchess::Side::Black);
        } else if (word == "quit") {
            break;
        }
    }
}

}  // namespace manual
