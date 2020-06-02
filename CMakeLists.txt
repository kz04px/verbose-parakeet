cmake_minimum_required(VERSION 3.10)

# Project
project(Swizles VERSION 1.0 LANGUAGES CXX)

# Find packages
find_package(Catch2 CONFIG REQUIRED)

# Base directory relative includes
include_directories(.)
include_directories(./libs/libchess/src/)

# Flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pthread")
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
    src/protocols/uci/extensions.cpp
    src/protocols/uci/uci.cpp
)

# Add test executable
add_executable(
    swizzles-test
    tests/main.cpp
    tests/uci.cpp
    src/options.cpp
    src/protocols/uci/uci.cpp
    src/protocols/uci/extensions.cpp
)

set_property(TARGET swizzles-test PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE FALSE)

target_link_libraries(swizzles "${CMAKE_CURRENT_LIST_DIR}/libs/libchess/build/static/libchess.a")
target_link_libraries(swizzles-test Catch2::Catch2 "${CMAKE_CURRENT_LIST_DIR}/libs/libchess/build/static/libchess.a")
