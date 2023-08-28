//
// Created by sangjun on 23. 8. 28.
//

#ifndef CAMEL_AMR_PROJECTS_V1_SIMUL_MAIN_HPP
#define CAMEL_AMR_PROJECTS_V1_SIMUL_MAIN_HPP

#include <iostream>
#include <bits/stdc++.h>
#include <memory>
#include <vector>
#include <tuple>
#include <cmath>
#include <stack>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "nav_msgs/msg/odometry.hpp"
//#include "amr_msg_interfaces/msg/grid_map_info.hpp"
#include "astar/Astar.hpp"
#include "ObsDetection/ObsDetection.hpp"
#include "DynamicObstacle/DynamicObstacle.hpp"
#include "Visualize/Map_In_Out.hpp"
#include "Variables/Variable.hpp"
#include "Variables/mapinfo.hpp"

const int num_obs = 1; // number of moving obstacle
const int sensor_range = 10; // Sensing distance

using Twist = geometry_msgs::msg::Twist;
using LaserScan = sensor_msgs::msg::LaserScan;
using Odometry = nav_msgs::msg::Odometry;
//using GridMapInfo = amr_msg_interfaces::msg::GridMapInfo;

class ParkingNode : public rclcpp::Node {
private:
    rclcpp::Publisher<Twist>::SharedPtr m_pub;
    rclcpp::Subscription<LaserScan>::SharedPtr m_sub;
    rclcpp::Subscription<Odometry>::SharedPtr m_sub_odom;
    Twist m_twist_msg;

    double heading;
    double xpos;
    double ypos;
    time_t timer;
    int MapCounter;

    Astar_planning ASTAR;
    coordinate mapsize;
    int map[200][200];
    coordinate start_point;
    coordinate end_point;
    std::stack<coordinate> traj;
//    Map_In_Out MapIO;
    DynamicObstacle obs[num_obs];
    coordinate present_pos;
    coordinate next_pos;
    ObsDetection *pO_D;
    int step;
    int count;

public:
    ParkingNode();
    void sub_callback(const LaserScan::SharedPtr msg);
    void odom_callback(const Odometry::SharedPtr msg);
    int star_position(int CurrentX, int CurrentY);
    void control_star_position(int dict);
    ~ParkingNode();
};

#endif //CAMEL_AMR_PROJECTS_V1_SIMUL_MAIN_HPP
