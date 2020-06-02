#include "options.hpp"

namespace options {

Spin hash{"Hash", 1, 2048, 32};
Spin threads{"Threads", 1, 32, 1};
Spin contempt{"Contempt", -1000, 1000, 0};
Combo test{"Test", 0, {"Test1", "Test2", "Test3"}};

}  // namespace options
