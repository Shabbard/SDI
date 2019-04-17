cmake_minimum_required(VERSION 3.13)
project(SDI)

set(CMAKE_CXX_STANDARD 14)

include_directories(headers)

add_executable(SDI
        headers/Browser.h
        headers/FileHandler.h
        headers/Film.h
        headers/GUI.h
        headers/Material.h
        src/Browser.cpp
        src/FileHandler.cpp
        src/Film.cpp
        src/GUI.cpp
        src/main.cpp
        src/Material.cpp
        src/SDI-tests.cpp)
