include_directories(
        ${PROJECT_SOURCE_DIR}/include/containers
        ${PROJECT_SOURCE_DIR}/include/scene/sensors
        ${PROJECT_SOURCE_DIR}/include/scene/geometry
        ${PROJECT_SOURCE_DIR}/include/utils)

add_executable(Ray_Tracer_Tests_run
        containerTests.cpp
        sceneTests.cpp
        utilsTests.cpp collisionTest.cpp)

target_link_libraries(Ray_Tracer_Tests_run
        container
        geometry
        gtest
        gtest_main
        lighting
        sensors
        utils)