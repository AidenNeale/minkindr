cmake_minimum_required(VERSION 3.8)
project(minkindr)

find_package(Threads REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect headers and sources
file(GLOB_RECURSE MINKINDR_HEADERS "include/*.h" "include/*.hpp")
# file(GLOB_RECURSE MINKINDR_SOURCES "src/*.cpp") # Uncomment if you have sources

# Create interface library for header-only, or use add_library for sources
add_library(minkindr INTERFACE)
target_include_directories(minkindr INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(minkindr INTERFACE Eigen3::Eigen Threads::Threads)

# Install headers
install(DIRECTORY include/ DESTINATION include)

# Install the interface library (for downstream CMake projects)
install(TARGETS minkindr EXPORT minkindrTargets)
install(EXPORT minkindrTargets
    FILE minkindrTargets.cmake
    NAMESPACE minkindr::
    DESTINATION lib/cmake/minkindr
)

# Tests
enable_testing()
add_executable(minkindr_tests
    test/test-main.cc
    test/test-rotation.cc
    test/test-sim3.cc
    test/test-transformation.cc
    test/test-transformation-2d.cc
)
target_include_directories(minkindr_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(minkindr_tests PRIVATE minkindr GTest::GTest GTest::Main Threads::Threads Eigen3::Eigen)
add_test(NAME minkindr_tests COMMAND minkindr_tests)