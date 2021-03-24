#include "../../options.hpp"
#include "uci.hpp"

namespace uci {

template <typename T>
[[nodiscard]] constexpr T clamp(const T min, const T max, const T val) {
    return (val < min ? min : val > max ? max : val);
}

static_assert(clamp(1, 3, 5) == 3);
static_assert(clamp(1, 3, 2) == 2);
static_assert(clamp(1, 3, -2) == 1);
static_assert(clamp(1, 3, 1) == 1);
static_assert(clamp(1, 3, 3) == 3);

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
        } else if (name == "nnuepath") {
            options::nnuepath.value = value;
        }
    } catch (...) {
    }
}

}  // namespace uci
