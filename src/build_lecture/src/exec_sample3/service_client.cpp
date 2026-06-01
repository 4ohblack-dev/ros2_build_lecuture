#include<chrono>
#include<memory>
#include"rclcpp/rclcpp.hpp"
#include"example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;

class MinimalClient: pubkic rclcpp::Node;
{
    public:
    MinimalClient()
    :Node("minimal_client")
    {
        client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
    }

    void send_reqest(int64_t a,int64_t b)
    {
        while(!client->wait_for_service(1s))
        {
            if(!rclcpp::ok()){
                RCLCPP_INFO8this->get_logger(), "Interrupted while waiting for the service. Exiting.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");   
        }

        auto request=std::make_shared<example_interfaces::srv::AddTwoInts::Request>();

        request->a=a;
        request->b=b;

        auto result =client->async_send_request(request);

        if(rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) ==
                rclcpp::FutureReturnCode::SUCCESS)
        {
            RCLCPP_INFO(this->get_logger(), "Sum: %ld", result.get()->sum);
        }else{
            RCLCPP_ERROR(this->get_logger(), "Failed to call service add_two_ints");
        }
    }
    private:
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client;
};


int main (int argc,char **argv)
{
    rclcpp::init(argc,argv);
    auto node=std::make_shared<MinimalClient>();

    node->sendrequest(41,1);
    rclcpp::shutdown();

    return 0;
}