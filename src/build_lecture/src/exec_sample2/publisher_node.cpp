#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

/*
:: → 「～の中にある（概念、部屋）」名前空間、クラス名、型名
*/
//namespace → 関数や名前がかぶらないように区分けする（PCのフォルダと同じ）

using namespace std::chrono_literals;//コード内で直感的な時間の単位が書けるようになる

class MinimalPublisher : public rclcpp::Node//rclcpp::Nodeという親クラスを継承して自分のクラスを作るのが一般的
{
    //子クラスのインスタンスが作られるとき、子クラスの初期化が始まる前に、まず親クラスの初期化が必要となる。
    public:
    MinimalPublisher()//ノードが作られる
    :Node("minimal_publisher")//親クラスに名前を投げて通信基盤を準備（新しく生まれるノードに名前を付け、起動）
    ,count(0)//自身のカウンターを0にリセットする
    {
        publisher = this->create_publisher<std_msgs::msg::String>("topic",10);
        //this → ヘッダファイルから継承した親クラスの関数create_publisher（トピックの発信窓口を新規開設する関数）を呼び出す
        //<std_msgs::msg::String>窓口の設定（文字列型の通信）、トピックの名前は"topic",10個だけデータを保持する
        timer = this->create_wall_timer(
            500ms, std::bind(&MinimalPublisher::timer_callback,this)
        );//0.5秒ごとに後ろで用意しているtimer_callback関数を実行するようにタイマーをセット
    }
    private:
    void timer_callback()
    {
        auto message = std_msgs::msg::String();//message箱を用意し、その中のdataという変数に文字列を入れていく
        message.data = "Hello, ROS2! Count: "+std::to_string(count++);
        RCLCPP_INFO(this->get_logger(),"Publishing: '%s",message.data.c_str());
        //ログ出力で、INFOは定期的なログ。
        //第2引数は画面に表示したい文章のフォーマット
        //第3引数は%sの部分に入れたい内容（.c_str()を付けることでC言語でも読み取れる形に変換する）
        publisher->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
    size_t count; 
};


int main(int argc,char *argv[])
{
    rclcpp::init(argc,argv);//初期化
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    //std::make_shared → ROS2ではインスタンス生成にもっともよく用いられ、インスタンスそのものではなく「インスタンスがメモリのどこにあるか」を示すポインタの状態で、実体を作ってくれる
    //速攻spin関数（イベントが起きるまで待機する）に投げているため、インスタンスが死なずに生き残る
    rclcpp::shutdown();
    return 0;
}