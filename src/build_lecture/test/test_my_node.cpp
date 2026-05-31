#include<gtest/gtest.h>
#include"rclcpp/rclcpp.hpp"

TEST(NodeTestPkg, DummyTest){
    int a =1;
    int b = 2;
    EXPECT_EQ(a+b,3);
}


int main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);
    rclcpp::init(argc, argv);
    int result = RUN_ALL_TESTS();
    rclcpp::shutdown();
    return result;
}