#include "qsearch.hpp"
#include "eval/eval.hpp"

namespace classic {

[[nodiscard]] int qsearch(libchess::Position &pos, int alpha, const int beta) {
    const auto stand_pat = eval(pos);

    if (stand_pat >= beta) {
        return beta;
    }

    if (alpha < stand_pat) {
        alpha = stand_pat;
    }

    for (const auto move : pos.legal_captures()) {
        pos.makemove(move);
        const auto score = -qsearch(pos, -beta, -alpha);
        pos.undomove();

        if (score >= beta) {
            return beta;
        }

        if (score > alpha) {
            alpha = score;
        }
    }

    return alpha;
}

}  // namespace classic
