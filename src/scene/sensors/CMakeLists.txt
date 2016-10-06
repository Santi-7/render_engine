set(SOURCE_FILES
        pinhole.cpp)

set(HEADER_FILES
        ../../../include/scene/sensors/camera.hpp
        ../../../include/scene/sensors/pinhole.hpp)

include_directories(
        ../../../include/scene/sensors)

add_library(sensors STATIC ${SOURCE_FILES} ${HEADER_FILES})