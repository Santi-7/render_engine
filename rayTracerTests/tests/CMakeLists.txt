include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ../../include
        ../../include/containers)

add_executable(RayTracerTests_run
        containerTests.cpp)

target_link_libraries(RayTracerTests_run container gtest gtest_main)
