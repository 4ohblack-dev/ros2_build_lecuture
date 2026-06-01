cmake_minimum_required(VERSION 3.8)#Cmakeのバージョン指定
project(build_lecture)#プロジェクトの名前を指定（後から{PROJECT_NAME}を使って使いまわせる）

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
#もし使っているC++コンパイラが GCC または Clang（Linuxの標準的なコンパイラ）だったら、コードの警告（Warning）を厳しめにチェックするモード（-Wall -Wextra -Wpedantic）を有効に
#ライブラリのビルドに必要な外部パッケージをPC内から探してくる
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED) 

#ソースコードをコンパイルして、実行ファイル（バイナリ）を作る
add_executable(talker src/exec_sample2/publisher_node.cpp)
#ament_target_dependencies(talker rclcpp std_msgs)#作った実行ファイルに、探してきたライブラリを紐づける
ament_target_dependencies(talker rclcpp std_msgs)
target_include_directories(talker PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)#talkerをビルドするとき、どこにある.hppを読み込むべきかを指定
target_compile_features(talker PUBLIC cxx_std_17)#talkerをコンパイルするときのC++の規格の設定

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

ament_package()#ここまでの設定をすべてまとめてROS2の正式なパッケージとして最終登録