#include <catch2/catch.hpp>
#include <libchess/position.hpp>
#include <string>
#include "../../src/search/controller.hpp"
#include "../../src/search/greedy/search.hpp"

auto info_handler = [](int depth, int score, std::uint64_t nodes, int time, const PV &pv) {};

TEST_CASE("Greedy - Movetime") {
    constexpr std::array<int, 3> movetimes = {20, 100, 200};
    auto pos = libchess::Position{"startpos"};

    for (const auto movetime : movetimes) {
        controller.reset();
        controller.set_movetime(movetime);
        const auto t0 = std::chrono::high_resolution_clock::now();
        const auto [bestmove, _] = greedy::search(pos, info_handler);
        const auto t1 = std::chrono::high_resolution_clock::now();
        const auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
        REQUIRE(dt.count() <= movetime + 50);
    }
}
