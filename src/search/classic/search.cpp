#include "search.hpp"
#include <cassert>
#include <functional>
#include <libchess/position.hpp>
#include "../controller.hpp"
#include "../pv.hpp"
#include "alphabeta.hpp"
#include "stack.hpp"

namespace classic {

std::pair<libchess::Move, libchess::Move> search(libchess::Position pos) {
    return search(pos, [](int depth, int score, std::uint64_t nodes, int time, const PV &pv) {});
}

std::pair<libchess::Move, libchess::Move> search(libchess::Position pos, const info_printer info) {
    libchess::Move bestmove;
    libchess::Move ponder;

    const auto legal_moves = pos.legal_moves();
    if (legal_moves.empty()) {
        return {};
    } else if (legal_moves.size() == 1) {
        return {legal_moves.at(0), {}};
    }

    // Calculate time strategy
    controller.meh();

    // Create search stack
    std::vector<Stack> ss{129};
    for (std::size_t i = 0; i < ss.size(); ++i) {
        ss.at(i).ply = i;
    }

    // Iterative deepening
    do {
        const auto score = alphabeta(pos, &ss.at(0), -mate_score, mate_score, controller.depth());

        assert(ss.at(0).pv.size() > 0);
        assert(legal_pv(pos, ss.at(0).pv));

        if (controller.depth() > 1 && controller.should_stop()) {
            break;
        }

        info(controller.depth(), score, controller.nodes(), controller.time_elapsed().count(), ss.at(0).pv);

        bestmove = ss.at(0).pv.at(0);
        ponder = ss.at(0).pv.size() > 1 ? ss.at(0).pv.at(1) : libchess::Move{};
        controller.increment_depth();
    } while (!controller.should_stop());

    assert(pos.is_legal(bestmove));

    return {bestmove, ponder};
}

}  // namespace classic
