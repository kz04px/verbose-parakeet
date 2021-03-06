cmake_minimum_required(VERSION 3.10)

# Project
project(Swizzles VERSION 1.0 LANGUAGES CXX)

# Base directory relative includes
include_directories(.)
include_directories(./libs/libchess/src/)
include_directories(./libs/catch2/)

# Find packages
find_package(Threads REQUIRED)

# Flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add engine executable
add_executable(
    swizzles
    src/main.cpp

    src/options.cpp

    # Protocols
    src/protocols/uci/isready.cpp
    src/protocols/uci/listen.cpp
    src/protocols/uci/moves.cpp
    src/protocols/uci/position.cpp
    src/protocols/uci/search.cpp
    src/protocols/uci/setoption.cpp
    src/protocols/uci/uci.cpp
    src/protocols/uci/ucinewgame.cpp
    src/protocols/uci/extensions/display.cpp
    src/protocols/uci/extensions/eval.cpp
    src/protocols/uci/extensions/perft.cpp
    src/protocols/uci/extensions/split.cpp
    src/protocols/manual/display.cpp
    src/protocols/manual/listen.cpp
    src/protocols/manual/play.cpp

    src/search/pv.cpp
    src/search/controller.cpp

    src/search/greedy/eval.cpp
    src/search/greedy/search.cpp

    src/search/classic/alphabeta.cpp
    src/search/classic/search.cpp
    src/search/classic/qsearch.cpp
    src/search/classic/eval/eval.cpp
    src/search/classic/eval/phase.cpp

    # libchess
    libs/libchess/src/attackers.cpp
    libs/libchess/src/is_legal.cpp
    libs/libchess/src/libchess
    libs/libchess/src/predict_hash.cpp
    libs/libchess/src/checkers.cpp
    libs/libchess/src/king_allowed.cpp
    libs/libchess/src/makemove.cpp
    libs/libchess/src/set_fen.cpp
    libs/libchess/src/check_evasions.cpp
    libs/libchess/src/legal_captures.cpp
    libs/libchess/src/movegen.cpp
    libs/libchess/src/square_attacked.cpp
    libs/libchess/src/count_moves.cpp
    libs/libchess/src/legal_moves.cpp
    libs/libchess/src/perft.cpp
    libs/libchess/src/squares_attacked.cpp
    libs/libchess/src/get_fen.cpp
    libs/libchess/src/legal_noncaptures.cpp
    libs/libchess/src/pinned.cpp
    libs/libchess/src/undomove.cpp
)

# Add test executable
add_executable(
    swizzles-test
    tests/main.cpp
    tests/uci.cpp

    tests/classic/mates.cpp
    tests/classic/movetime.cpp
    tests/classic/stalemate.cpp
    tests/classic/underpromote.cpp
    tests/classic/50moves.cpp

    tests/greedy/50moves.cpp
    tests/greedy/mates.cpp
    tests/greedy/movetime.cpp
    tests/greedy/search.cpp
    tests/greedy/stalemate.cpp
    tests/greedy/underpromote.cpp

    src/options.cpp

    # Protocols
    src/protocols/uci/isready.cpp
    src/protocols/uci/listen.cpp
    src/protocols/uci/moves.cpp
    src/protocols/uci/position.cpp
    src/protocols/uci/search.cpp
    src/protocols/uci/setoption.cpp
    src/protocols/uci/uci.cpp
    src/protocols/uci/ucinewgame.cpp
    src/protocols/uci/extensions/display.cpp
    src/protocols/uci/extensions/eval.cpp
    src/protocols/uci/extensions/perft.cpp
    src/protocols/uci/extensions/split.cpp

    src/search/pv.cpp
    src/search/controller.cpp

    src/search/greedy/eval.cpp
    src/search/greedy/search.cpp

    src/search/classic/alphabeta.cpp
    src/search/classic/search.cpp
    src/search/classic/qsearch.cpp
    src/search/classic/eval/eval.cpp
    src/search/classic/eval/phase.cpp

    # libchess
    libs/libchess/src/attackers.cpp
    libs/libchess/src/is_legal.cpp
    libs/libchess/src/libchess
    libs/libchess/src/predict_hash.cpp
    libs/libchess/src/checkers.cpp
    libs/libchess/src/king_allowed.cpp
    libs/libchess/src/makemove.cpp
    libs/libchess/src/set_fen.cpp
    libs/libchess/src/check_evasions.cpp
    libs/libchess/src/legal_captures.cpp
    libs/libchess/src/movegen.cpp
    libs/libchess/src/square_attacked.cpp
    libs/libchess/src/count_moves.cpp
    libs/libchess/src/legal_moves.cpp
    libs/libchess/src/perft.cpp
    libs/libchess/src/squares_attacked.cpp
    libs/libchess/src/get_fen.cpp
    libs/libchess/src/legal_noncaptures.cpp
    libs/libchess/src/pinned.cpp
    libs/libchess/src/undomove.cpp
)

set_property(TARGET swizzles-test PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE FALSE)
target_link_libraries(swizzles PUBLIC Threads::Threads)
target_link_libraries(swizzles-test PUBLIC Threads::Threads)
