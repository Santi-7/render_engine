set(SOURCE_FILES
        color.cpp
        image.cpp
        matrix.cpp
        point.cpp
        vect.cpp)

set(HEADER_FILES
        ../../include/containers/color.hpp
        ../../include/containers/image.hpp
        ../../include/containers/matrix.hpp
        ../../include/containers/point.hpp
        ../../include/containers/vect.hpp)

include_directories(
        ../../include/containers)

add_library(container STATIC ${SOURCE_FILES} ${HEADER_FILES})