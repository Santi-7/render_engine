include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ../../include
        ../../include/containers
        ../../include/utils)

add_executable(RayTracerTests_run
        containerTests.cpp
        utilsTests.cpp)

target_link_libraries(RayTracerTests_run container utils gtest gtest_main)