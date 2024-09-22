cmake_minimum_required(VERSION 3.28)
project(somethingBeautiful)

set(CMAKE_CXX_STANDARD 20)

add_executable(somethingBeautiful main.cpp
        Attacker.h
        Hero.h
        Enemy.h
        Dragon.h
        termcolor/termcolor.h
        Elf.h)

include_directories(/usr/local/include)
find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(somethingBeautiful sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
