cmake_minimum_required(VERSION 3.21)
project(CLionHomeworks)

set(CMAKE_CXX_STANDARD 14)

add_executable(CLionHomeworks main.cpp)
add_executable(first_homework n-sliding-puzzle/n-sliding-puzzle.cpp)
add_executable(second_homework nqueens/nqueens.cpp)
add_executable(third_homework tsp/tsp.cpp)
add_executable(fourth_homework nought_and_crosses/nought_and_crosses.cpp)
add_executable(fifth_homework naive-bayes/naive-bayes.cpp)
