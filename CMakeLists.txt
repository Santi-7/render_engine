cmake_minimum_required(VERSION 3.5)
project(Ray_Tracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

include_directories(
        include/containers
        include/utils)

set(SOURCE_FILES
        src/containers/matrix.cpp include/containers/matrix.hpp
        src/containers/point.cpp include/containers/point.hpp
        src/containers/vect.cpp include/containers/vect.hpp
        src/utils/transformationMatrix.cpp include/utils/transformationMatrix.hpp
        src/main.cpp)

add_executable(Ray_Tracer ${SOURCE_FILES})