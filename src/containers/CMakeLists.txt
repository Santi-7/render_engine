set(SOURCE_FILES
        color.cpp
        image.cpp
        matrix.cpp
        point.cpp
        vect.cpp)

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/containers/color.hpp
        ${PROJECT_SOURCE_DIR}/include/containers/image.hpp
        ${PROJECT_SOURCE_DIR}/include/containers/matrix.hpp
        ${PROJECT_SOURCE_DIR}/include/containers/point.hpp
        ${PROJECT_SOURCE_DIR}/include/containers/vect.hpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/containers)

add_library(container STATIC ${SOURCE_FILES} ${HEADER_FILES})