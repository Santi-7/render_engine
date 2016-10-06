include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ../../include/containers
        ../../include/utils)

add_executable(Ray_Tracer_Tests_run
        containerTests.cpp
        utilsTests.cpp)

target_link_libraries(Ray_Tracer_Tests_run container utils gtest gtest_main)