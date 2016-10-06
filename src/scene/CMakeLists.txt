set(SOURCE_FILES
        scene.cpp)

set(HEADER_FILES
        ../../include/scene/scene.hpp)

include_directories(
        ../../include/scene
        ../../include/scene/geometry
        ../../include/scene/sensors)

add_subdirectory(geometry)
add_subdirectory(lighting)
add_subdirectory(materials)
add_subdirectory(sensors)

add_library(scene STATIC ${SOURCE_FILES} ${HEADER_FILES})