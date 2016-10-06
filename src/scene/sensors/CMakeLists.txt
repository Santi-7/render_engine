set(SOURCE_FILES
        pinhole.cpp
        camera.cpp)

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/scene/sensors/camera.hpp
        ${PROJECT_SOURCE_DIR}/include/scene/sensors/pinhole.hpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/scene/sensors)

add_library(sensors STATIC ${SOURCE_FILES} ${HEADER_FILES})