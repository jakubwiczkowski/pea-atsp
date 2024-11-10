cmake_minimum_required(VERSION 3.29)
project(pea_atsp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

add_executable(pea_atsp
        src/main.cpp
        src/menu/menu.h
        src/menu/menu.cpp
        src/graph/graph.cpp
        src/graph/graph.h
        src/atsp/algorithm.h
        src/atsp/solution.h
        src/type/types.h
        src/atsp/little/little.cpp
        src/atsp/little/little.h
        src/atsp/bruteforce/iterative/bruteforce_iter.cpp
        src/atsp/bruteforce/iterative/bruteforce_iter.h
        src/atsp/dynamic/dynamic.cpp
        src/atsp/dynamic/dynamic.h)

target_compile_options(pea_atsp PRIVATE -O3)