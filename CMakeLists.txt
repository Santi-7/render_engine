cmake_minimum_required(VERSION 3.5)
project(Ray_Tracer)

ADD_DEFINITIONS( -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\" )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3")

set(SOURCE_FILES
        main.cpp)

add_executable(Ray_Tracer_run
        main.cpp)

include_directories(
        include/containers)

add_subdirectory(lib)
add_subdirectory(rayTracerTests)
add_subdirectory(src)

target_link_libraries(Ray_Tracer_run container)