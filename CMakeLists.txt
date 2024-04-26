cmake_minimum_required(VERSION 3.28)
project(StoreSimulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(StoreSimulation main.cpp
        Queue.cpp
        LinkedList.cpp
        simulation.cpp)
