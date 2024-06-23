cmake_minimum_required(VERSION 3.19)
project(OOP_Redoven4_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP_Redoven4_1 main.cpp Averager.cpp Averager.hpp BacklogPublisher.cpp BacklogPublisher.hpp MovingAverager.cpp MovingAverager.hpp PeriodicSampler.cpp PeriodicSampler.hpp Repository.cpp Repository.hpp SimplePublisher.cpp SimplePublisher.hpp Message.cpp Message.hpp Subscriber.cpp Subscriber.hpp Publisher.cpp Publisher.hpp)