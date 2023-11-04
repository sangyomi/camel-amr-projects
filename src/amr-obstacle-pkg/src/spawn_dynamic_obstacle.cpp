#include <iostream>
#include <fstream>
#include <string>
#include "ament_index_cpp/get_package_share_directory.hpp"
#include "gazebo_msgs/srv/spawn_entity.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

const double PI = 3.14159265358979323846;

class SpawnRobot : public rclcpp::Node
{
public:
    SpawnRobot()
            : Node("gazebo_model_spawner")
    {
        client_ = create_client<gazebo_msgs::srv::SpawnEntity>("/spawn_entity");

        while (!client_->wait_for_service(std::chrono::seconds(1))) {
            RCLCPP_ERROR(this->get_logger(), "Service not available, waiting again...");
        }

        urdf_file_path_ = ament_index_cpp::get_package_share_directory("amr-gazebo-pkg") + "/urdf/diffbot_amr_obstacle.urdf";

        req_ = std::make_shared<gazebo_msgs::srv::SpawnEntity::Request>();
    }

    void sendRequest(const std::string& robotName, double x_coordinate, double y_coordinate, double initial_heading)
    {
        req_->name = robotName;
        std::ifstream file(urdf_file_path_);
        std::stringstream buffer;
        buffer << file.rdbuf();
        req_->xml = buffer.str();
        req_->robot_namespace = robotName;
        req_->initial_pose.position.x = x_coordinate;
        req_->initial_pose.position.y = y_coordinate;
        req_->initial_pose.position.z = 0.3;

        tf2::Quaternion q;
        q.setRPY(0.0, 0.0, initial_heading);
        tf2::convert(q, req_->initial_pose.orientation);

        RCLCPP_INFO(this->get_logger(), "==== Sending service request to `/spawn_entity` for robot: " + robotName + " ====");
        auto future = client_->async_send_request(req_);

        rclcpp::spin_until_future_complete(shared_from_this(), future);

        if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            try {
                auto response = future.get();
                RCLCPP_DEBUG(this->get_logger(), "==== Service Call Done ====");
                RCLCPP_DEBUG(this->get_logger(), "Status_message: " + response->status_message);
            } catch (const std::exception& e) {
                throw std::runtime_error("Exception while calling service: " + std::string(e.what()));
            }
        }

        RCLCPP_WARN(this->get_logger(), "==== Shutting down node. ====");
    }


private:
    rclcpp::Client<gazebo_msgs::srv::SpawnEntity>::SharedPtr client_;
    std::string urdf_file_path_;
    gazebo_msgs::srv::SpawnEntity::Request::SharedPtr req_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SpawnRobot>();
//    node->sendRequest("dynamic_obstacle_1", 0.0, 0.0, 0);
//    node->sendRequest("dynamic_obstacle_2", -9.0, 8.0, -PI/2);
    node->sendRequest("dynamic_obstacle_3", 8.0, -9.0, PI/2);
//    node->sendRequest("dynamic_obstacle_4", -8.0, -8.0, PI/2);
//    node->sendRequest("dynamic_obstacle_5", 8.0, -5.0, 0);
    rclcpp::shutdown();
    return 0;
}

