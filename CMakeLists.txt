cmake_minimum_required(VERSION 3.28)
project(DragonsGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(DragonsGame main.cpp
        Attacker.h
        Hero.h
        Enemy.h
        Dragon.h
        termcolor/termcolor.h
        Elf.h)

include_directories(/usr/local/include)
find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(DragonsGame sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

add_subdirectory(KatLib)
target_link_libraries(DragonsGame KatLib)
