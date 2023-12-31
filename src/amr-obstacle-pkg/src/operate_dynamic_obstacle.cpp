#include <iostream>
#include <memory>
#include <fstream>
#include <cmath>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"

using Odometry = nav_msgs::msg::Odometry;
using Twist = geometry_msgs::msg::Twist;

class RobotController : public rclcpp::Node
{
public:
    RobotController()
            : Node("robot_controller")
    {
        for (int i = 2; i <= 3; ++i) {
            std::string robot_name = "dynamic_obstacle_" + std::to_string(i);
            std::string cmd_vel_topic = "/" + robot_name + "/cmd_vel";
            std::string odom_topic = "/" + robot_name + "/odom";

            auto velocity_publisher = create_publisher<Twist>(cmd_vel_topic, 10);
            velocity_publishers_.push_back(velocity_publisher);

            auto odometer_subscriber = create_subscription<Odometry>(
                    odom_topic, 10,
                    std::bind(&RobotController::odom_callback, this, std::placeholders::_1)
            );
            odometer_subscribers_.push_back(odometer_subscriber);
        }

        start_time_ = clock.now();
    }

private:
    std::vector<rclcpp::Publisher<Twist>::SharedPtr> velocity_publishers_;
    std::vector<rclcpp::Subscription<Odometry>::SharedPtr> odometer_subscribers_;

    Twist m_twist_msg;

    double heading;

    rclcpp::Clock clock;
    rclcpp::Time start_time_;
    rclcpp::Time now_time_;

    void odom_callback(const Odometry::SharedPtr msg) {
        double x = msg->pose.pose.orientation.x;
        double y = msg->pose.pose.orientation.y;
        double z = msg->pose.pose.orientation.z;
        double w = msg->pose.pose.orientation.w;
        double siny_cosp = 2 * (w * z + x * y);
        double cosy_cosp = 1 - 2 * (y * y + z * z);
        double yaw = atan2(siny_cosp,cosy_cosp);
        heading = yaw;
        now_time_ = clock.now();

        int elapsed_time = int(now_time_.seconds() - start_time_.seconds());
        RCLCPP_INFO(get_logger(), "Time: %d", elapsed_time);

        for (int i = 0; i < velocity_publishers_.size(); ++i) {
            if (elapsed_time % 14 < 7) {
                moveRobotForward(velocity_publishers_[i]);
            } else {
                moveRobotBackward(velocity_publishers_[i]);
            }
        }
    }

    void moveRobotForward(const rclcpp::Publisher<Twist>::SharedPtr& publisher) {
        m_twist_msg.linear.x = 0.9;
        m_twist_msg.angular.z = 0.0;
        publisher->publish(m_twist_msg);
    }

    void moveRobotBackward(const rclcpp::Publisher<Twist>::SharedPtr& publisher) {
        m_twist_msg.linear.x = -0.9;
        m_twist_msg.angular.z = 0.0;
        publisher->publish(m_twist_msg);
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotController>();
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
