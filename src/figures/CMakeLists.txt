set(SOURCE_FILES
        sphere.cpp)

set(HEADER_FILES
        ../../include/figures/sphere.hpp)

include_directories(
        ../../include/containers
        ../../include/figures)

add_library(utils STATIC ${SOURCE_FILES} ${HEADER_FILES})