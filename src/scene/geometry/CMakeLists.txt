set(SOURCE_FILES
        sphere.cpp)

set(HEADER_FILES
        ../../include/scene/geometry/shape.hpp
        ../../include/scene/geometry/sphere.hpp)

include_directories(
        ../../include/containers
        ../../include/scene/geometry)

add_library(geometry STATIC ${SOURCE_FILES} ${HEADER_FILES})