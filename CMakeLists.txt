cmake_minimum_required(VERSION 3.5)
project(Ray_Tracer)

ADD_DEFINITIONS( -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\" )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -fpermissive -Wall")

set(SOURCE_FILES
        main.cpp)

add_executable(render
        main.cpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/containers
        ${PROJECT_SOURCE_DIR}/include/scene
        ${PROJECT_SOURCE_DIR}/include/scene/geometry
        ${PROJECT_SOURCE_DIR}/include/scene/lighting
        ${PROJECT_SOURCE_DIR}/include/scene/sensors
        ${PROJECT_SOURCE_DIR}/include/utils)

add_subdirectory(src)

target_link_libraries(render
                      container
                      geometry
		      lighting
		      scene
		      sensors
		      utils
		      pthread)
