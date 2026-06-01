cmake_minimum_required(VERSION 3.8)
project(build_lecture)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
# std_msgsの代わりに、あるいは追加でexample_interfacesを読み込む
find_package(example_interfaces REQUIRED) 

# --- サーバー側の設定 ---
add_executable(service_server src/exec_sample3/service_server.cpp)# パスは環境に合わせて調整してください
ament_target_dependencies(service_server rclcpp example_interfaces)
target_compile_features(service_server PUBLIC cxx_std_17)

# --- クライアント側の設定 ---
add_executable(service_client src/exec_sample3/service_client.cpp)
ament_target_dependencies(service_client rclcpp example_interfaces)
target_compile_features(service_client PUBLIC cxx_std_17)

# --- インストール設定 ---
install(TARGETS
  service_server
  service_client
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()