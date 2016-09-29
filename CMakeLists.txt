cmake_minimum_required(VERSION 3.6)
project(ass3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES
    ConnectFour/Game.cpp
    ConnectFour/Game.hpp
    ConnectFour/Grid.cpp
    ConnectFour/Grid.hpp
    ConnectFour/Player.cpp
    ConnectFour/Player.hpp
    ConnectFour/SuperGame.cpp
    ConnectFour/SuperGame.hpp
    test.cpp)

add_executable(ass3 ${SOURCE_FILES})