cmake_minimum_required(VERSION 3.8)
project(build_lecture)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# Publisher のバイナリ作成と依存関係の紐付け
add_executable(talker src/publisher_node.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

# Subscriber のバイナリ作成と依存関係の紐付け
add_executable(listener src/subscriber_node.cpp)
ament_target_dependencies(listener rclcpp std_msgs)



target_include_directories(my_cpp_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(my_cpp_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  my_cpp_node
  "rclcpp"
)

# 実行ファイルを適切な場所にインストール
install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()