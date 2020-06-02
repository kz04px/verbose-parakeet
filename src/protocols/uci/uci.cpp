#include "../uci.hpp"
#include <cassert>
#include <iostream>
#include <libchess/position.hpp>
#include <sstream>
#include "../../options.hpp"
#include "extensions.hpp"

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

template <typename T>
[[nodiscard]] constexpr T clamp(const T min, const T max, const T val) {
    return (val < min ? min : val > max ? max : val);
}

static_assert(clamp(1, 3, 5) == 3);
static_assert(clamp(1, 3, 2) == 2);
static_assert(clamp(1, 3, -2) == 1);
static_assert(clamp(1, 3, 1) == 1);
static_assert(clamp(1, 3, 3) == 3);

void uci() {
    std::cout << "id name Swizzles\n";
    std::cout << "id author kz04px\n";

    std::cout << options::hash << "\n";
    std::cout << options::threads << "\n";
    std::cout << options::contempt << "\n";
    std::cout << options::test << "\n";

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

void go(libchess::Position &pos, std::stringstream &ss) {
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
        const auto val = std::stoi(value);
        if (name == "Hash") {
            options::hash.val = clamp(options::hash.min, options::hash.max, val);
        } else if (name == "Threads") {
            options::threads.val = clamp(options::threads.min, options::threads.max, val);
        } else if (name == "Contempt") {
            options::contempt.val = clamp(options::contempt.min, options::contempt.max, val);
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
            isready();
            break;
        } else if (word == "setoption") {
            setoption(ss);
        } else if (word == "quit") {
            return;
        }
    }

    auto pos = libchess::Position{"startpos"};

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
            // stop();
        } else if (word == "setoption") {
            setoption(ss);
        } else if (word == "print" || word == "display" || word == "board") {
            extension::display(pos);
        } else if (word == "perft") {
            extension::perft(pos, ss);
        } else if (word == "split") {
            extension::split(pos, ss);
        } else if (word == "quit") {
            break;
        } else {
            // if (Options::checks["debug"].get()) {
            //    std::cout << "info unknown UAI command \"" << word << "\""
            //               << std::endl;
            //}
        }
    }
}

}  // namespace uci