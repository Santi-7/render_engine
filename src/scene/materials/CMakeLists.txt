set(SOURCE_FILES
        material.cpp checkerBoard.cpp crossHatchModifier.cpp)

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/scene/materials/material.hpp
        ${PROJECT_SOURCE_DIR}/include/scene/materials/checkerBoard.hpp
        ${PROJECT_SOURCE_DIR}/include/scene/materials/crossHatchModifier.hpp
        ${PROJECT_SOURCE_DIR}/include/scene/materials/vectorModifier.hpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/utils
        ${PROJECT_SOURCE_DIR}/include/scene/materials)

add_library(materials STATIC ${SOURCE_FILES} ${HEADER_FILES})