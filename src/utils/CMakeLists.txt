set(SOURCE_FILES
        intersections.cpp
        poseTransformationMatrix.cpp
        transformationMatrix.cpp)

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/utils/intersections.hpp
        ${PROJECT_SOURCE_DIR}/include/utils/poseTransformationMatrix.hpp
        ${PROJECT_SOURCE_DIR}/include/utils/transformationMatrix.hpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/containers
        ${PROJECT_SOURCE_DIR}/include/utils)

add_library(utils STATIC ${SOURCE_FILES} ${HEADER_FILES})