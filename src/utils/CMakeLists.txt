set(SOURCE_FILES
        transformationMatrix.cpp
        ppmImage.cpp)

set(HEADER_FILES
        ../../include/utils/transformationMatrix.hpp
        ../../include/utils/ppmImage.hpp)

include_directories(
        ../../include/containers
        ../../include/utils)

add_library(utils STATIC ${SOURCE_FILES} ${HEADER_FILES})