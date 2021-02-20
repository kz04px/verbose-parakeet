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
};

namespace options {

extern Spin hash;
extern Spin threads;
extern Spin contempt;
extern Combo searchtype;

}  // namespace options

#endif
