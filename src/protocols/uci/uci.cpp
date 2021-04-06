#include "uci.hpp"
#include <iostream>
#include "../../options.hpp"

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
    os << " type string";
    os << " default " << string.value;
    return os;
}

void uci() {
    std::cout << "id name Swizzles\n";
    std::cout << "id author kz04px\n";

    std::cout << options::hash << "\n";
    std::cout << options::threads << "\n";
    std::cout << options::contempt << "\n";
    std::cout << options::searchtype << "\n";

    std::cout << "uciok" << std::endl;
}

}  // namespace uci
