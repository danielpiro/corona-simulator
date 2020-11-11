cmake_minimum_required(VERSION 3.17)
project(spl_assignment)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(spl_assignment
        include/Agent.h
        include/Graph.h
        include/json.hpp
        include/Session.h
        include/Tree.h
        src/Agent.cpp
        src/Graph.cpp
        src/main.cpp
        src/Session.cpp
        src/Tree.cpp)
