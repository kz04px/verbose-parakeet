#include <catch2/catch.hpp>
#include <libchess/position.hpp>
#include <string>
#include "../../src/search/classic/search.hpp"
#include "../../src/search/controller.hpp"

static auto info_handler = [](int depth, int score, std::uint64_t nodes, int time, const PV &pv) {};

TEST_CASE("Classic - Underpromotions") {
    const std::pair<std::string, std::string> tests[] = {
        {"6n1/5P1k/5Q2/8/8/8/8/7K w - - 0 1", "f7f8n"},
        {"7k/8/8/8/8/5q2/5p1K/6N1 b - - 0 1", "f2f1n"},
    };

    for (const auto &[fen, movestr] : tests) {
        INFO(fen);
        controller.reset();
        controller.set_depth(2);
        auto pos = libchess::Position{fen};
        const auto [bestmove, ponder] = classic::search(pos, info_handler);
        REQUIRE(static_cast<std::string>(bestmove) == movestr);
    }
}
