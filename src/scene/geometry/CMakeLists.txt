set(SOURCE_FILES
        sphere.cpp)

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/scene/geometry/shape.hpp
        ${PROJECT_SOURCE_DIR}/include/scene/geometry/sphere.hpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/containers
        ${PROJECT_SOURCE_DIR}/include/scene/geometry)

add_library(geometry STATIC ${SOURCE_FILES} ${HEADER_FILES})