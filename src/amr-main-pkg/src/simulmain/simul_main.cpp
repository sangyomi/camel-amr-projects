//
// Created by sangjun on 23. 8. 24.
//
#include <iostream>
#include <bits/stdc++.h>
#include <memory>
#include <vector>
#include <tuple>
#include <cmath>
#include <ctime>
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "PathPlanning/Astar.hpp"
#include "Visualize/Map_In_Out.hpp"
#include "ObsDetection/ObsDetection.hpp"
#include "DynamicObstacle/DynamicObstacle.hpp"

using LaserScan = sensor_msgs::msg::LaserScan;

const int num_obs = 5; // number of moving obstacle
const int sensor_range = 10; // Sensing distance

class ParkingNode : public rclcpp::Node {
private:
    rclcpp::Subscription<LaserScan>::SharedPtr m_sub;
    coordinate mapsize; // map size of column
    int map[100][100];
    coordinate start_point;
    coordinate end_point;
    std::stack<coordinate> traj;
    DynamicObstacle obs[num_obs];
    ObsDetection *pO_D;
    coordinate present_pos;

public:
    ParkingNode() : Node("robot_parking_node") {
        RCLCPP_INFO(get_logger(), "Parking Node Created");

        map[100][100] = {0,};

        Map_In_Out MapIO;
        Astar_planning *ASTAR;
        ASTAR = new Astar_planning;
        MapIO.Map_Input(start_point, end_point, mapsize, map);

        traj = ASTAR->Astar(start_point, end_point, mapsize, map);
        delete ASTAR;
        MapIO.printMap(map, traj);
        srand((unsigned int) time(NULL));
        DynamicObstacle obs[num_obs];

        for (int i = 0; i < num_obs; i++) {
            obs[i].Initialize();
            obs[i].ApplyToMap(map);
        }
        std::cout << std::endl;
        present_pos = traj.top();
        traj.pop();
        ObsDetection *pO_D;
        pO_D = new ObsDetection;
        pO_D->SetNumObstacle(num_obs);
        pO_D->SetSensorRange(sensor_range);

        m_sub = create_subscription<LaserScan>(
                "diffbot_amr/scan", 10,
                std::bind(&ParkingNode::sub_callback, this, std::placeholders::_1));

    }
    void sub_callback(const LaserScan::SharedPtr msg) {
        coordinate next_pos = traj.top();
        for (int i = 0; i < num_obs; i++)
            obs[i].UpdateObstacle(map, mapsize); // update each obstacle's path -> moving

        pO_D->loadRobotStatus(present_pos, next_pos);
        int *obs_count = new int;
        *obs_count = pO_D->isObstacleDetected(map,mapsize);
        if (*obs_count >= 1) {
            // 장애물이 인식이되면 경계 및 경로 수정까지
            std::cout << "ObsDetected!!!\n";
            for(int i = 0; i < *obs_count; i++){
                coordinate obs_loc = pO_D->GetDetectedObsLoc();
                pO_D->SetObsTraj(obs_loc);
            }
        }
        delete obs_count;
        map[present_pos.first][present_pos.second] = 0;
        present_pos = next_pos;
        map[present_pos.first][present_pos.second] = 5; //AMR should move at the end of obstacle detection

//        MapIO.printMap(map, traj);
//        sleep(1);

        traj.pop();
    }
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);

    auto parking_node = std::make_shared<ParkingNode>();
    rclcpp::spin(parking_node);
    rclcpp::shutdown();

    return 0;
}
