set(SOURCE_FILES
        ppmImage.cpp
        transformationMatrix.cpp)

set(HEADER_FILES
        ../../include/utils/ppmImage.hpp
        ../../include/utils/transformationMatrix.hpp)

include_directories(
        ../../include/containers
        ../../include/utils)

add_library(utils STATIC ${SOURCE_FILES} ${HEADER_FILES})