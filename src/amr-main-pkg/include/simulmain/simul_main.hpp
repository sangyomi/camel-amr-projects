//
// Created by sangjun on 23. 8. 28.
//

#ifndef CAMEL_AMR_PROJECTS_V1_SIMUL_MAIN_HPP
#define CAMEL_AMR_PROJECTS_V1_SIMUL_MAIN_HPP

#include "Variables/Variable.hpp"
#include "Variables/mapinfo.hpp"
#include "Variables/SharedMemory.h"
#include <bits/stdc++.h>
#include <memory>
#include <tuple>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <chrono>
#include <QApplication>
#include <QThread>
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "astar/Astar.hpp"
#include "ObsDetection/ObsDetection.hpp"
#include "ClusteringDynamicObs/ClusteringDynamicObs.hpp"
#include "ObsDetection/PathChanger.hpp"

const int num_obs = 1; // number of moving obstacle
const int sensor_range = 10; // Sensing distance

using Twist = geometry_msgs::msg::Twist;
using LaserScan = sensor_msgs::msg::LaserScan;
using Odometry = nav_msgs::msg::Odometry;

class ParkingNode : public rclcpp::Node {
private:
    rclcpp::Publisher<Twist>::SharedPtr m_pub;
    rclcpp::Subscription<LaserScan>::SharedPtr m_sub;
    rclcpp::Subscription<Odometry>::SharedPtr m_sub_odom;
    Twist m_twist_msg;

    double heading;
    double xpos;
    double ypos;
    std::vector<coordinate> a;

    int MapCounter;
    ClusteringDynamicObs Cluster;

    Astar_planning ASTAR;
    coordinate mapsize;
    int map[200][200];
    coordinate end_point;
    std::stack<coordinate> traj;
    coordinate present_pos;
    coordinate next_pos;
    ObsDetection ObsDec;
    int step;
    int count;
    int cnt = 0;
    int AddedPathNum = 1;
    PathChanger P_C;
    std::vector<coordinate> PATH;
    coordinate StartPoint = {10,90};
    coordinate EndPoint = {90,10};
    void ClearCostMap();
    void GetDuration();

public:
    ParkingNode();
    void sub_callback(const LaserScan::SharedPtr msg);
    void odom_callback(const Odometry::SharedPtr msg);
    int star_position(int CurrentX, int CurrentY);
    void control_star_position(int dict);
    ~ParkingNode();
    void clearSharedMemory();
    void StartSimulation();
    PathChangeData PathChangeDatas;

};

#endif //CAMEL_AMR_PROJECTS_V1_SIMUL_MAIN_HPP