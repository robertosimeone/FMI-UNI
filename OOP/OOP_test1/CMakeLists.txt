cmake_minimum_required(VERSION 3.19)
project(OOP_test1)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP_test1 main.cpp cmake-build-debug/NamedObject.cpp cmake-build-debug/NamedObject.hpp)