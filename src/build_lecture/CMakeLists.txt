cmake_minimum_required(VERSION 3.8)
project(build_lecture)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# 【修正】実際のファイルパス（src/exec_sample1/main.cpp）に合わせました
add_executable(my_cpp_node src/exec_sample1/main.cpp)

target_include_directories(my_cpp_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(my_cpp_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  my_cpp_node
  "rclcpp"
)

install(TARGETS my_cpp_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()