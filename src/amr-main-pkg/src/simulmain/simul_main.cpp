//
// Created by sangjun on 23. 8. 24.
//
#include "simulmain/simul_main.hpp"

ParkingNode::ParkingNode() : Node("robot_parking_node") {

    start_point = std::make_pair(0,0);
    end_point = std::make_pair(80,80);

    RCLCPP_INFO(get_logger(), "Parking Node Created");

    for (int i = 0; i < num_obs; i++) {
        obs[i].Initialize();
        obs[i].ApplyToMap(map);
    }
    std::cout << std::endl;

    pO_D = new ObsDetection;
    pO_D->SetNumObstacle(num_obs);
    pO_D->SetSensorRange(sensor_range);

    step = 0;
    count = 0;

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
    std::cout << int(xpos) << std::endl;
    std::cout << int(ypos) << std::endl;

    start_point = std::make_pair(int(xpos+10)*5,int(ypos+10)*5);
    ASTAR = new Astar_planning;
    MapIO.Map_Input(start_point, end_point, mapsize, map);

    traj = ASTAR->Astar(start_point, end_point, mapsize, map);
    delete ASTAR;
    MapIO.printMap(map, traj);


    if(step == 0)
    {
        present_pos = traj.top();
        traj.pop();
        next_pos = traj.top();
    }

    for (int i = 0; i < num_obs; i++)
        obs[i].UpdateObstacle(map, mapsize); // update each obstacle's path -> moving

    pO_D->loadRobotStatus(present_pos, next_pos);
    int *obs_count = new int;
    *obs_count = pO_D->isObstacleDetected(map, mapsize, step);

    if (*obs_count >= 1) {
        std::cout << "ObsDetected!!!\n";
        pO_D->CollisionDetection(traj);
    }
    delete obs_count;

//    MapIO.printMap(map, traj);
    sleep(1);

    if(int(xpos)*5 == next_pos.first && int(ypos)*5 == next_pos.second)
    {
        map[present_pos.first][present_pos.second] = 0;
        present_pos = next_pos;
        map[present_pos.first][present_pos.second] = 5; //AMR should move at the end of obstacle detection

        traj.pop();
        step++;
        count++;
    }
    else if(count == 1)
    {
        present_pos = traj.top();
        traj.pop();
        coordinate next_pos = traj.top();
        count--;
    }
    else
    {
        //move
    }

    std::cout << "heading : " << heading << std::endl;
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

ParkingNode::~ParkingNode()
{
    delete pO_D;
}

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto parking_node = std::make_shared<ParkingNode>();
    rclcpp::spin(parking_node);
    rclcpp::shutdown();

    return 0;
}
