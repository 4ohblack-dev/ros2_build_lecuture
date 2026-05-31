cmake_minimum_required(VERSION 3.8)
project(build_lecture)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED) # 🔥【追加】std_msgs の検索が必要です

# --- talker ノードの設定 ---
# ソースファイル（publisher_node.cpp）から「talker」という実行ファイルを作成
add_executable(talker src/exec_sample2/publisher_node.cpp)
# talker が使用する外部ライブラリを紐付け
ament_target_dependencies(talker rclcpp std_msgs)
# 🔥【修正】my_cpp_node ではなく、作った「talker」に対して設定を適用
target_include_directories(talker PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(talker PUBLIC cxx_std_17) # C++17を要求

# --- listener ノードの設定 ---
# ソースファイル（subsriber_node.cpp）から「listener」という実行ファイルを作成
add_executable(listener src/exec_sample2/subscriber_node.cpp)
# listener が使用する外部ライブラリを紐付け
ament_target_dependencies(listener rclcpp std_msgs)
# 🔥【修正】こちらも「listener」に対して設定を適用
target_include_directories(listener PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(listener PUBLIC cxx_std_17)

# --- インストール設定 ---
install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()