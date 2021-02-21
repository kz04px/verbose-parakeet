#include "../uci.hpp"
#include <cassert>
#include <iostream>
#include <libchess/position.hpp>
#include <sstream>
#include <thread>
#include "../../options.hpp"
#include "../../search/controller.hpp"
#include "../../search/search.hpp"
#include "extensions.hpp"
// Searches
#include "../../search/classic/eval.hpp"
#include "../../search/classic/search.hpp"
#include "../../search/random/search.hpp"

namespace uci {

inline std::ostream &operator<<(std::ostream &os, const Spin &spin) {
    os << "option";
    os << " name " << spin.name;
    os << " type spin";
    os << " default " << spin.val;
    os << " min " << spin.min;
    os << " max " << spin.max;
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const Combo &combo) {
    os << "option";
    os << " name " << combo.name;
    os << " type combo";
    os << " default " << combo.choices.at(combo.selected);
    for (const auto &name : combo.choices) {
        os << " var " << name;
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const String &string) {
    os << "option";
    os << " name " << string.name;
    os << " value " << string.value;
    return os;
}

template <typename T>
[[nodiscard]] constexpr T clamp(const T min, const T max, const T val) {
    return (val < min ? min : val > max ? max : val);
}

static_assert(clamp(1, 3, 5) == 3);
static_assert(clamp(1, 3, 2) == 2);
static_assert(clamp(1, 3, -2) == 1);
static_assert(clamp(1, 3, 1) == 1);
static_assert(clamp(1, 3, 3) == 3);

std::thread search_thread;

void uci() {
    std::cout << "id name Swizzles\n";
    std::cout << "id author kz04px\n";

    std::cout << options::hash << "\n";
    std::cout << options::threads << "\n";
    std::cout << options::contempt << "\n";
    std::cout << options::searchtype << "\n";

    std::cout << "uciok" << std::endl;
}

void isready() {
    std::cout << "readyok" << std::endl;
}

void ucinewgame(libchess::Position &pos) {
    pos.set_fen("startpos");
}

void position(libchess::Position &pos, std::stringstream &ss) {
    std::string word;
    std::string fen;
    ss >> word;

    // Position
    if (word == "startpos") {
        fen = "startpos";
        ss >> word;
    } else if (word == "fen") {
        // Collect fen string
        while (ss >> word && word != "moves") {
            if (fen != "") {
                fen += " ";
            }
            fen += word;
        }
    } else {
        return;
    }

    pos.set_fen(fen);

    if (word == "moves") {
        moves(pos, ss);
    }
}

void moves(libchess::Position &pos, std::stringstream &ss) {
    std::string word;
    while (ss >> word) {
        const auto legal_moves = pos.legal_moves();
        bool found = false;
        for (const auto &move : legal_moves) {
            if (word == static_cast<std::string>(move)) {
                found = true;
                pos.makemove(move);
                break;
            }
        }
        if (!found) {
            break;
        }
    }
}

void stop() {
    controller.stop();
    if (search_thread.joinable()) {
        search_thread.join();
    }
}

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

    const auto &[bestmove, ponder] = player::search(pos, uci_printer);
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

void setoption(std::stringstream &ss) {
    std::string word;

    ss >> word;
    if (word != "name") {
        return;
    }

    // Collect option name
    std::string name = "";
    while (ss >> word && word != "value") {
        if (name != "") {
            name += " ";
        }
        name += word;
    }

    // Collect option value
    std::string value = "";
    while (ss >> word) {
        if (value != "") {
            value += " ";
        }
        value += word;
    }

    try {
        if (name == "Hash") {
            const auto val = std::stoi(value);
            options::hash.val = clamp(options::hash.min, options::hash.max, val);
        } else if (name == "Threads") {
            const auto val = std::stoi(value);
            options::threads.val = clamp(options::threads.min, options::threads.max, val);
        } else if (name == "Contempt") {
            const auto val = std::stoi(value);
            options::contempt.val = clamp(options::contempt.min, options::contempt.max, val);
        } else if (name == "SearchType") {
            options::searchtype.set(value);
        }
    } catch (...) {
    }
}

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
        player::search = classic::search;
        player::eval = classic::eval;
    } else if (options::searchtype.get() == "Random") {
        player::search = rando::search;
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
