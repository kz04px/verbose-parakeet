#include "../../src/search/greedy/search.hpp"
#include <catch2/catch.hpp>
#include <libchess/position.hpp>
#include <string>
#include "../../src/search/controller.hpp"

auto info_handler = [](int depth, int score, std::uint64_t nodes, int time, const PV &pv) {};

TEST_CASE("Greedy - Search") {
    const std::pair<std::string, std::string> tests[] = {
        {"4k3/8/8/8/8/8/5q2/4K3 w - - 0 1", "e1f2"},
        {"4k3/5Q2/8/8/8/8/8/4K3 b - - 0 1", "e8f7"},
        {"4k3/8/8/1r3q2/3N4/8/8/4K3 w - - 0 1", "d4f5"},
        {"4k3/8/8/3n4/1R3Q2/8/8/4K3 b - - 0 1", "d5f4"},
        {"4k3/8/8/1r3p2/3N4/8/8/4K3 w - - 0 1", "d4b5"},
        {"4k3/8/8/3n4/1R3P2/8/8/4K3 b - - 0 1", "d5b4"},
        {"4k3/1R6/R6q/8/8/8/8/4K3 w - - 0 1", "a6a8"},
        {"4k3/8/8/8/8/r6Q/1r6/4K3 b - - 0 1", "a3a1"},
    };

    for (const auto &[fen, movestr] : tests) {
        controller.reset();
        controller.set_depth(2);
        auto pos = libchess::Position{fen};
        const auto [bestmove, ponder] = greedy::search(pos, info_handler);
        REQUIRE(static_cast<std::string>(bestmove) == movestr);
    }
}
