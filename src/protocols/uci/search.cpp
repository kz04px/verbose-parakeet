#include "../../search/search.hpp"
#include <iostream>
#include <thread>
#include "../../search/controller.hpp"
#include "uci.hpp"

namespace uci {

std::thread search_thread;

void search_wrapper(libchess::Position pos) {
    info_printer uci_printer = [](int depth, int score, std::uint64_t nodes, int time, const PV &pv) {
        std::cout << "info";
        std::cout << " depth " << depth;
        std::cout << " score cp " << score;
        std::cout << " nodes " << nodes;
        std::cout << " time " << time;
        if (time > 0) {
            std::cout << " nps " << static_cast<std::uint64_t>(1000 * nodes / time);
        }
        if (!pv.empty()) {
            std::cout << " pv";
            for (const auto &move : pv) {
                std::cout << " " << move;
            }
        }
        std::cout << std::endl;
    };

    const auto &[bestmove, ponder] = search_func(pos, uci_printer);
    std::cout << "bestmove " << bestmove;
    if (ponder) {
        std::cout << " ponder " << ponder;
    }
    std::cout << std::endl;
}

void go(libchess::Position &pos, std::stringstream &ss) {
    stop();
    controller.reset();
    controller.set_us(pos.turn());
    std::string word;
    while (ss >> word) {
        if (word == "depth" && ss >> word) {
            controller.set_depth(std::stoi(word));
        } else if (word == "movetime" && ss >> word) {
            controller.set_movetime(std::stoi(word));
        } else if (word == "nodes" && ss >> word) {
            controller.set_nodes(std::stoi(word));
        } else if (word == "wtime" && ss >> word) {
            controller.set_wtime(std::stoi(word));
        } else if (word == "btime" && ss >> word) {
            controller.set_btime(std::stoi(word));
        } else if (word == "winc" && ss >> word) {
            controller.set_winc(std::stoi(word));
        } else if (word == "binc" && ss >> word) {
            controller.set_binc(std::stoi(word));
        } else if (word == "infinite" && ss >> word) {
            controller.set_infinite();
        }
    }

    search_thread = std::thread(search_wrapper, pos);
}

void stop() {
    controller.stop();
    if (search_thread.joinable()) {
        search_thread.join();
    }
}

}  // namespace uci
