set(SOURCE_FILES
        matrix.cpp
        point.cpp
        vect.cpp
        ../../include/containers/color.hpp)

set(HEADER_FILES
        ../../include/containers/matrix.hpp
        ../../include/containers/point.hpp
        ../../include/containers/vect.hpp color.cpp)

include_directories(
        ../../include/containers)

add_library(container STATIC ${SOURCE_FILES} ${HEADER_FILES})