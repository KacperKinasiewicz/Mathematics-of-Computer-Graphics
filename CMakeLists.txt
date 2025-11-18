cmake_minimum_required(VERSION 4.0)
project(Mathematics_of_Computer_Graphics)

set(CMAKE_CXX_STANDARD 14)

include_directories("Laboratorium 4 - kwaterniony")

add_executable(Mathematics_of_Computer_Graphics
        "Laboratorium 4 - kwaterniony/Kwaternion.cpp"
        "Laboratorium 4 - kwaterniony/Kwaternion.h"
        "Laboratorium 4 - kwaterniony/main.cpp")
