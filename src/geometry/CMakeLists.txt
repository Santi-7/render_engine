set(SOURCE_FILES
        sphere.cpp)

set(HEADER_FILES
        ../../include/geometry/shape.hpp
        ../../include/geometry/sphere.hpp)

include_directories(
        ../../include/containers
        ../../include/geometry)

add_library(geometry STATIC ${SOURCE_FILES} ${HEADER_FILES})