set(SOURCE_FILES
        pointLight.cpp simpleAreaLight.cpp)

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/scene/lighting/lightSource.hpp
        ${PROJECT_SOURCE_DIR}/include/scene/lighting/pointLight.hpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/scene/lighting)

add_library(lighting STATIC ${SOURCE_FILES} ${HEADER_FILES})