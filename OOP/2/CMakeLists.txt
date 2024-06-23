cmake_minimum_required(VERSION 3.19)
project(2)

set(CMAKE_CXX_STANDARD 14)

add_executable(2 main.cpp Developer.cpp Developer.hpp LeavingRequest.cpp LeavingRequest.hpp PromotionRequest.cpp PromotionRequest.hpp Request.cpp Request.hpp TeamLead.cpp TeamLead.hpp)