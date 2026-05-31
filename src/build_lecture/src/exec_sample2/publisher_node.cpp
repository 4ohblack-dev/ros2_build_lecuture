#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
    public:
    MinimalPublisher()
    :Node("minimal_publisher"),count(0)
    {
        publisher = this->create_publisher<std_msgs::msg::String>("topic",10);
        timer = this->create_wall_timer(
            500ms, std::bind(&MinimalPublisher::timer_callback,this)
        );
    }
    private:
    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        message.data = "Hllo, ROS2! Count: "+std::to_string(count++);
        RCLCPP_INFO(this->get_logger(),"Publishing: '%s",message.data.c_str());
        publisher->publish(message);
    }

    rclcpp::TimerBase::SharePtr timer;
    rclcpp::Publisher<std_msgs::msg::String>::SharePtr publisher;
    size_t count; 
};


int main(int argc,char *argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    rclcpp::shutdown();
    return 0;
}