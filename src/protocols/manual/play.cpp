#include "play.hpp"
#include <iostream>
#include <libchess/position.hpp>
#include <string>
#include "../../search/classic/search.hpp"
#include "../../search/controller.hpp"
#include "display.hpp"

namespace manual {

info_printer printer = [](int depth, int score, std::uint64_t nodes, int time, const PV &pv) {};

void play(const std::string &fen, const libchess::Side human) {
    auto pos = libchess::Position{fen};

    controller.set_us(!human);
    controller.set_depth(2);

    std::cout << "\n";
    display(pos, human == libchess::Side::Black);
    std::cout << "\n";

    while (true) {
        if (pos.turn() == human) {
            std::string word;
            std::cin >> word;

            if (word == "quit") {
                break;
            } else {
                const auto moves = pos.legal_moves();
                for (const auto &move : moves) {
                    if (static_cast<std::string>(move) == word) {
                        pos.makemove(move);
                        std::cout << "\n";
                        display(pos, human == libchess::Side::Black);
                        std::cout << "\n";
                        break;
                    }
                }
            }
        } else {
            std::cout << "Computer thinking...\n";
            controller.reset();
            const auto &[bestmove, ponder] = classic::search(pos, printer);
            std::cout << "Move " << static_cast<std::string>(bestmove) << "\n\n";
            pos.makemove(bestmove);
            display(pos, human == libchess::Side::Black);
            std::cout << "\n";
        }
    }
}

}  // namespace manual
