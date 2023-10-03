//
// Created by sangjun on 23. 8. 24.
//
#include "simulmain/simul_main.hpp"
#include "../Amr_UI/mainwindow.h"

pSHM sharedMemory;
DSHM dynamicSharedMemory;

ParkingNode::ParkingNode() : Node("robot_parking_node") {

    RCLCPP_INFO(get_logger(), "Parking Node Created");
    startTime = std::chrono::steady_clock::now();
    step = 0;
    MapCounter = 0;
    PATH.push_back(StartPoint);
    PATH.push_back(EndPoint);
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
    auto endTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    double duration = static_cast<double>(elapsedTime.count());
    MapCounter++;
    int xAstar = int((sharedMemory->xpos+10)*5);
    int yAstar = int((sharedMemory->ypos+10)*5);
    coordinate AmrLoc = {xAstar,yAstar};
    PATH.front() = AmrLoc;
    if(PathAdded){
        if(PATH.size() != 2)
            PATH.erase(PATH.begin()+1,PATH.end()-1);
        PATH.insert(PATH.begin()+1,P_C.SafeLocation.begin(),P_C.SafeLocation.end());
        PathAdded = false;
    }
    if(abs(xAstar-PATH[1].first) < 2 && abs(yAstar-PATH[1].second) < 2)
    {
        PATH.erase(PATH.begin()+1);
    }
    if(PATH.size() == 1){
        std::cout << "Calculation Finished!";
        return;
    }
    std::cout << "----------------------------" << std::endl;
    std::cout << "Present AMR Location: " << "(" << xAstar << "," << yAstar << ")" <<std::endl;
    std::cout << "ABSTime: " << duration << std::endl;
    for(int i = 0; i < PATH.size(); i++){
        std::cout << PATH[i].first << ", " << PATH[i].second << "\n";
    }

    Cluster.UpdateDynamicObstacle(msg->ranges, ASTAR.Mapmatrix, sharedMemory->heading, sharedMemory->xpos, sharedMemory->ypos, MapCounter);
    O_D.SaveObsInfo(Cluster.LabelingArray, duration);
    O_D.LinearRegression();
    O_D.Prediction(5,1000);
    O_D.Pred_Print();
    ASTAR.startAstar(PATH);
    ASTAR.AmrFuturePath(ASTAR.traj, m_twist_msg.linear.x);
    for(int i = 0 ; i < O_D.GetNum_ObsPredPoint() ; i++) {
        auto temp = O_D.GetObsPredPoint(i);
        int CollisionPoint = P_C.CollisionPrediction(ASTAR.futuretraj, temp);
        if (CollisionPoint == -1) {
            continue;
        }
        else {
            int ColPredictedPointX = int(dynamicSharedMemory.obsLog[i].coeff_data.c1 +
                    dynamicSharedMemory.obsLog[i].coeff_data.a * (duration + 1000 * CollisionPoint));
            int ColPredictedPointY = int(dynamicSharedMemory.obsLog[i].coeff_data.c2 +
                    dynamicSharedMemory.obsLog[i].coeff_data.b * (duration + 1000 * CollisionPoint));
            coordinate ColPredictedPoint = std::make_pair(ColPredictedPointX, ColPredictedPointY);
            std::cout << "충돌 시간[ms] 및 위치: " << duration + 1000 * CollisionPoint << "[ms], (" << ColPredictedPointX << ", " << ColPredictedPointY << ")\n";
            O_D.Prediction(20, 400);
            PathChangeDatas.ColPredictedPoint = ColPredictedPoint;
            PathChangeDatas.ObsTrajSample = O_D.GetObsPredPoint(i);
            PathChangeDatas.AmrLoc = std::make_pair(xAstar, yAstar);
            PathChangeDatas.AmrVel = m_twist_msg.linear.x;
            PathChangeDatas.ObsCoeffData = dynamicSharedMemory.obsLog[i].coeff_data;
            P_C.GetSafeLoc(PathChangeDatas, duration);
            if(P_C.SafeLocation.front().first != -1)PathAdded = true;
            std::cout << P_C.SafeLocation.size() << "LOC \n";
            for (int i = 0; i < P_C.SafeLocation.size(); i++) {
                std::cout << "Alternative Path: (" << P_C.SafeLocation[i].first << ", " << P_C.SafeLocation[i].second
                          << ")\n";
            }
        }
        std::cout << std::endl;
        std::cout << CollisionPoint << "초 후 충돌합니다!!\n";
        std::cout << std::endl;
    }

    control_star_position(star_position(int((sharedMemory->xpos+10)*5), int((sharedMemory->ypos+10)*5)));

    while(!ASTAR.traj.empty())
    {
        ASTAR.traj.pop();
    }
//    ASTAR.PrintMap(); // PathPlanning Map
//    Cluster.PrintMap(); // Dynamic Obstacle Map
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
    sharedMemory->heading = yaw;
    sharedMemory->xpos = msg->pose.pose.position.x;
    sharedMemory->ypos = msg->pose.pose.position.y;
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
    float value = ASTAR.direction[dict] - sharedMemory->heading;
    if (value > 3.14) {value = value - 2*PI;}
    else if (value < -3.14) {value = value + 2*PI;}
    float turn_offset = 0.7 * (value);
//    std::cout << "Turn_offset: " << turn_offset << "\n\n";
    if (abs(turn_offset) > 0.005) {
        m_twist_msg.linear.x = 0.6;
        m_twist_msg.angular.z = turn_offset;
        m_pub->publish(m_twist_msg);
    }
}
ParkingNode::~ParkingNode()
{

}

void clearSharedMemory()
{
    sharedMemory->heading=0;
    sharedMemory->xpos=0;
    sharedMemory->ypos=0;
    dynamicSharedMemory.coeff_data.clear();
    dynamicSharedMemory.obsLog.clear();

}

void StartSimulation()
{
    sharedMemory = (pSHM)malloc(sizeof(SHM));
    clearSharedMemory();

}


class CommunicationThread : public QThread
{
public:
    void run() override
    {
        auto parking_node = std::make_shared<ParkingNode>();
        rclcpp::spin(parking_node);
        rclcpp::shutdown();
    }

};

int main(int argc, char ** argv)
{
    QApplication a(argc, argv);
    StartSimulation();
    MainWindow w;
    w.setWindowTitle("AMR_UI");
    rclcpp::init(argc, argv);
    CommunicationThread communicationThread;
    communicationThread.start();
    w.show();

    return a.exec();
}