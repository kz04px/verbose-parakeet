#include <catch2/catch.hpp>
#include <libchess/position.hpp>
#include <string>
#include "../../src/search/controller.hpp"
#include "../../src/search/greedy/search.hpp"

static auto info_handler = [](int depth, int score, std::uint64_t nodes, int time, const PV &pv) {};

TEST_CASE("Greedy - Fifty move draw") {
    const std::pair<std::string, std::string> tests[] = {
        {"7k/8/R7/1R6/7K/8/7P/8 w - - 99 1", "h2h3"},
        {"8/7p/8/7k/1r6/r7/8/7K b - - 99 1", "h7h6"},
        {"8/8/8/P7/8/6n1/3R4/R3K2k w Q - 99 1", "a5a6"},
        {"r3k2K/3r4/6N1/8/p7/8/8/8 b q - 99 1", "a4a3"},
    };

    for (const auto &[fen, movestr] : tests) {
        controller.reset();
        controller.set_depth(2);
        auto pos = libchess::Position{fen};
        const auto [bestmove, ponder] = greedy::search(pos, info_handler);
        REQUIRE(static_cast<std::string>(bestmove) == movestr);
    }
}
