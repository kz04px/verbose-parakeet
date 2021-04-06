#include <iostream>
#include "../../options.hpp"
#include "extensions/extensions.hpp"
#include "uci.hpp"
// Searches
#include "../../search/classic/eval/eval.hpp"
#include "../../search/classic/search.hpp"
#include "../../search/greedy/eval.hpp"
#include "../../search/greedy/search.hpp"
#include "../../search/random/search.hpp"

namespace uci {

search_type search_func = [](libchess::Position pos, const info_printer info) -> search_return { return {}; };
std::function<int(const libchess::Position &pos)> eval_func = [](const libchess::Position &pos) { return 0; };

void listen() {
    uci();

    std::string word;
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        std::stringstream ss{input};
        ss >> word;

        if (word == "isready") {
            break;
        } else if (word == "setoption") {
            setoption(ss);
        } else if (word == "quit") {
            return;
        }
    }

    // Set the search type
    if (options::searchtype.get() == "Classic") {
        search_func = classic::search;
        eval_func = classic::eval;
    } else if (options::searchtype.get() == "Greedy") {
        search_func = greedy::search;
        eval_func = greedy::eval;
    } else if (options::searchtype.get() == "Random") {
        search_func = rando::search;
    } else {
        return;
    }

    auto pos = libchess::Position{"startpos"};
    isready();

    while (true) {
        std::string input;
        std::getline(std::cin, input);
        std::stringstream ss{input};
        ss >> word;

        if (word == "ucinewgame") {
            ucinewgame(pos);
        } else if (word == "isready") {
            isready();
        } else if (word == "position") {
            position(pos, ss);
        } else if (word == "moves") {
            moves(pos, ss);
        } else if (word == "go") {
            go(pos, ss);
        } else if (word == "stop") {
            stop();
        } else if (word == "setoption") {
            setoption(ss);
        } else if (word == "print" || word == "display" || word == "board") {
            extension::display(pos);
        } else if (word == "perft") {
            extension::perft(pos, ss);
        } else if (word == "split") {
            extension::split(pos, ss);
        } else if (word == "eval") {
            extension::eval(pos);
        } else if (word == "quit") {
            break;
        }
    }

    stop();
}

}  // namespace uci
