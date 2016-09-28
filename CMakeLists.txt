cmake_minimum_required(VERSION 3.5)
project(Ray_Tracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(SOURCE_FILES
        src/main.cpp
        src/data/point.cpp src/data/point.hpp
        src/data/vect.cpp src/data/vect.hpp)

add_executable(Ray_Tracer ${SOURCE_FILES})