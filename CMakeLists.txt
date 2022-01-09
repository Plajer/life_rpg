cmake_minimum_required(VERSION 3.21)
project(life_rpg)

set(CMAKE_CXX_STANDARD 20)

add_executable(life_rpg main.cpp utils.cpp utils.h game.cpp game.h)
