set(SOURCE_FILES
        participativeMedia.cpp
        scene.cpp
        )

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/scene/participativeMedia.hpp
        ${PROJECT_SOURCE_DIR}/include/scene/scene.hpp
        ${PROJECT_SOURCE_DIR}/include/scene/sceneSamples.hpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/scene
        ${PROJECT_SOURCE_DIR}/include/scene/geometry
        ${PROJECT_SOURCE_DIR}/include/scene/lighting
        ${PROJECT_SOURCE_DIR}/include/scene/sensors
        ${PROJECT_SOURCE_DIR}/include/utils)

add_subdirectory(geometry)
add_subdirectory(lighting)
add_subdirectory(materials)
add_subdirectory(sensors)

add_library(scene STATIC ${SOURCE_FILES} ${HEADER_FILES})