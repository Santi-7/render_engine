set(SOURCE_FILES
        matrix.cpp
        point.cpp
        vect.cpp
        color.cpp
        image.cpp)

set(HEADER_FILES
        ../../include/containers/matrix.hpp
        ../../include/containers/point.hpp
        ../../include/containers/vect.hpp
        ../../include/containers/color.hpp
        ../../include/containers/image.hpp)

include_directories(
        ../../include/containers)

add_library(container STATIC ${SOURCE_FILES} ${HEADER_FILES})