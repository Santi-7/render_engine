set(SOURCE_FILES
        material.cpp)

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/scene/materials/material.hpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/utils
        ${PROJECT_SOURCE_DIR}/include/scene/materials)

add_library(materials STATIC ${SOURCE_FILES} ${HEADER_FILES})