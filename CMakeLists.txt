cmake_minimum_required(VERSION 3.5)
project(Ray_Tracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(SOURCE_FILES
        main.cpp)

add_executable(Ray_Tracer_run main.cpp)

include_directories(
        include
        include/containers)

add_subdirectory(src)
add_subdirectory(rayTracerTests)
add_subdirectory(include)

target_link_libraries(Ray_Tracer_run container)