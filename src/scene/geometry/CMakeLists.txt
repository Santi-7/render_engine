set(SOURCE_FILES
        plane.cpp
        sphere.cpp
        triangle.cpp
        meshTriangle.cpp
        mesh.cpp )

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/scene/geometry/plane.hpp
        ${PROJECT_SOURCE_DIR}/include/scene/geometry/shape.hpp
        ${PROJECT_SOURCE_DIR}/include/scene/geometry/sphere.hpp
        ${PROJECT_SOURCE_DIR}/include/scene/geometry/meshTriangle.hpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/containers
        ${PROJECT_SOURCE_DIR}/include/scene/geometry
        ${PROJECT_SOURCE_DIR}/include/utils)

add_library(geometry STATIC ${SOURCE_FILES} ${HEADER_FILES})