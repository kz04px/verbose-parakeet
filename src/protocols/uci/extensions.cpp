#include <chrono>
#include <iostream>
#include <libchess/position.hpp>
#include <sstream>
#include "../../options.hpp"
#include "../../search/search.hpp"
#include "../uci.hpp"

namespace uci::extension {

void perft(libchess::Position &pos, std::stringstream &ss) {
    int depth = 0;

    if (!(ss >> depth) || depth < 0) {
        return;
    }

    const auto t0 = std::chrono::high_resolution_clock::now();
    const auto nodes = pos.perft(depth);
    const auto t1 = std::chrono::high_resolution_clock::now();
    const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);

    std::cout << "info";
    std::cout << " depth " << depth;
    std::cout << " nodes " << nodes;
    std::cout << " time " << time.count();
    std::cout << std::endl;

    std::cout << "nodes " << nodes << std::endl;
}

void split(libchess::Position &pos, std::stringstream &ss) {
    int depth = 0;

    if (!(ss >> depth) || depth < 0) {
        return;
    }

    const auto legal_moves = pos.legal_moves();
    std::uint64_t total = 0;

    const auto t0 = std::chrono::high_resolution_clock::now();
    for (const auto &move : legal_moves) {
        pos.makemove(move);
        const auto nodes = pos.perft(depth);
        total += nodes;
        std::cout << move << " " << nodes << std::endl;
        pos.undomove();
    }
    const auto t1 = std::chrono::high_resolution_clock::now();
    const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);

    std::cout << "nodes " << total;
    std::cout << " time " << time.count();
    std::cout << std::endl;
}

void display(const libchess::Position &pos) {
    std::cout << pos << std::endl;
}

void eval(const libchess::Position &pos) {
    const auto score = player::eval(pos);
    std::cout << "info string eval " << score << std::endl;
}

}  // namespace uci::extension
