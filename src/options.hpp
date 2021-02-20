#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <map>
#include <string>
#include <vector>

struct Spin {
    std::string name;
    int min;
    int max;
    int val;
};

struct Combo {
    std::string name;
    std::size_t selected;
    std::vector<std::string> choices;

    const auto set(const std::string &option) noexcept {
        for (std::size_t i = 0; i < choices.size(); ++i) {
            if (choices[i] == option) {
                selected = i;
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] const auto &get() const {
        return choices.at(selected);
    }
};

namespace options {

extern Spin hash;
extern Spin threads;
extern Spin contempt;
extern Combo searchtype;

}  // namespace options

#endif
