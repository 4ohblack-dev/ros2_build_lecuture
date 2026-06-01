cmake_minimum_required(VERSION 3.8)
project(build_lecture)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED) 

add_executable(talker src/exec_sample2/publisher_node.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
target_include_directories(talker PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(talker PUBLIC cxx_std_17)

add_executable(listener src/exec_sample2/subscriber_node.cpp)
ament_target_dependencies(listener rclcpp std_msgs)
target_include_directories(listener PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(listener PUBLIC cxx_std_17)

install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()