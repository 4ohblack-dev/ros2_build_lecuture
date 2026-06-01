#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MinimalSubscriber : public rclcpp::Node
{
    public:
    MinimalSubscriber(const rclcpp::NodeOptions & options)
    :Node("minimal_subsciber",options)
    {
        subscription = this->create_subscription<std_msgs::msg::String>
        (
            "topic",10,std::bind(&MinimalSubscriber::topic_callback,this,std::placeholders::_1)
        );
        //bind(&MinimalSubscriber::topic_callback,this,std::placeholders::_1) → 裏側で自動起動してほしい関数の設定
    }
    private:
        void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
        {
            RCLCPP_INFO(this->get_logger(),"I heard: '%s'",msg->data.c_str());
        }
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription;
};

//int main(int argc,char *argv[])
//{
//    rclcpp::init(argc,argv);
//    rclcpp::spin(std::make_shared<MinimalSubscriber>());
//    rclcpp::shutdown();
//    return 0;
//}

int main(int argc,char *argv[])
{
    rclcpp::init(argc,argv);
    // 1. プロセス内通信を「有効（true）」にしたオプションを用意する
    rclcpp:NodeOptions options;
    options.use_intra_process_comms(true);
// 2. 同じオプションを使って、両方のノードのインスタンスを「同じメイン関数内」で作る
    auto talker_node=std::make_shared<MinimalPublisher>(options);
    auto listener_node=std::make_shared<MinimalSubscriber>(options);

    // 3. 「Executor（エグゼキュータ）」というまとめ役を用意する
    rclcpp::executors::SingleThreadedRxecutor executor;

    executor.add_node(talker_node);
    executor.add_node(listener_node);

    executor.spin();
    
    rclcpp::shutdown();
    return 0;
}