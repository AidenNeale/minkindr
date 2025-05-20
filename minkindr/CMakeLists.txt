cmake_minimum_required(VERSION 3.8)
project(minkindr)

find_package(ament_cmake REQUIRED)
find_package(Threads REQUIRED)
find_package(ament_cmake_gtest REQUIRED)
find_package(Eigen3 REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Install headers
install(DIRECTORY include/ DESTINATION include)

file(GLOB_RECURSE LibFiles "include/*")
add_custom_target(headers SOURCES ${LibFiles})

# Add gtest
ament_add_gtest(${PROJECT_NAME}_tests
  test/test-main.cc
  test/test-rotation.cc
  test/test-sim3.cc
  test/test-transformation.cc
  test/test-transformation-2d.cc
)
target_include_directories(${PROJECT_NAME}_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}_tests Threads::Threads Eigen3::Eigen)

ament_package()