//
// Created by sangjun on 23. 8. 24.
//
#include "simulmain/simul_main.hpp"
#define PI 3.14159265

ParkingNode::ParkingNode() : Node("robot_parking_node") {

    RCLCPP_INFO(get_logger(), "Parking Node Created");

    step = 0;
    MapCounter = 0;

    m_pub = create_publisher<Twist>("diffbot_amr/cmd_vel", 10);
    m_sub = create_subscription<LaserScan>(
            "diffbot_amr/scan", 10,
            std::bind(&ParkingNode::sub_callback, this, std::placeholders::_1));
    m_sub_odom = create_subscription<Odometry>(
            "/diffbot_amr/odom", 10,
            std::bind(&ParkingNode::odom_callback, this, std::placeholders::_1) );

}

void ParkingNode::sub_callback(const LaserScan::SharedPtr msg)
{
    MapCounter++;

    int xAstar = int((xpos+10)*5);
    int yAstar = int((ypos+10)*5);

    if(abs(xAstar-ASTAR.Destx[ASTAR.count]) < 3 && abs(yAstar-ASTAR.Desty[ASTAR.count]) < 3)
    {
        ASTAR.Mapmatrix[ASTAR.Destx[ASTAR.count]][ASTAR.Desty[ASTAR.count]] = 0;
        ASTAR.count++;
        if(ASTAR.count==3)
        {
            ASTAR.count-=3;
        }
    }
    else
    {
        Cluster.UpdateDynamicObstacle(msg->ranges, ASTAR.Mapmatrix, heading, xpos, ypos, MapCounter);
        ASTAR.startAstar(xAstar, yAstar);
    }

    control_star_position(star_position(int((xpos+10)*5), int((ypos+10)*5)));

    while(!ASTAR.traj.empty())
    {
        ASTAR.traj.pop();
    }
    std::cout << "Cycle time: "<< Cluster.timer_cycle << std::endl;

//    ASTAR.PrintMap(); // PathPlanning Map
    Cluster.PrintMap(); // Dynamic Obstacle Map
}

void ParkingNode::odom_callback(const Odometry::SharedPtr msg)
{
    double x = msg->pose.pose.orientation.x;
    double y = msg->pose.pose.orientation.y;
    double z = msg->pose.pose.orientation.z;
    double w = msg->pose.pose.orientation.w;
    double siny_cosp = 2 * (w * z + x * y);
    double cosy_cosp = 1 - 2 * (y * y + z * z);
    double yaw = atan2(siny_cosp,cosy_cosp);
    heading = yaw;
    xpos = msg->pose.pose.position.x;
    ypos = msg->pose.pose.position.y;
}

int ParkingNode::star_position(int CurrentX, int CurrentY)
{
    for (int i = 0 ; i < 4 ; ++i) {
        if (ASTAR.zmap[CurrentX + ASTAR.dx1[i]][CurrentY + ASTAR.dy1[i]] == '*') {
            return 2 * i + 2;
        }
        if (ASTAR.zmap[CurrentX + ASTAR.dx2[i]][CurrentY + ASTAR.dy2[i]] == '*') {
            return 2 * i + 1;
        }
    }
    return 0;
}

void ParkingNode::control_star_position(int dict)
{
    if (dict == 0)
    {
        std::cout << "++++++++++++++++++++++++++++++" << std::endl;
        rclcpp::shutdown();
    }
    float value = ASTAR.direction[dict] - heading;
    if (value > 3.14) {value = value - 2*PI;}
    else if (value < -3.14) {value = value + 2*PI;}
    float turn_offset = 0.7 * (value);
    std::cout << "Turn_offset: " << turn_offset << std::endl;
    if (abs(turn_offset) > 0.01) {
        m_twist_msg.linear.x = 0.4;
        m_twist_msg.angular.z = turn_offset;
        m_pub->publish(m_twist_msg);
    }
}


ParkingNode::~ParkingNode()
{
//    delete pO_D;
}

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto parking_node = std::make_shared<ParkingNode>();
    rclcpp::spin(parking_node);
    rclcpp::shutdown();

    return 0;
}
