include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include/containers
        ${PROJECT_SOURCE_DIR}/include/utils
        ${PROJECT_SOURCE_DIR}/include/scene/sensors)

add_executable(Ray_Tracer_Tests_run
        containerTests.cpp
        utilsTests.cpp
        sceneTests.cpp)

target_link_libraries(Ray_Tracer_Tests_run container sensors lighting geometry materials utils gtest gtest_main)