//
// Created by sangjun on 23. 8. 24.
//
#include "simulmain/simul_main.hpp"
#include "../Amr_UI/mainwindow.h"

pSHM sharedMemory;
DSHM dynamicSharedMemory;
std::chrono::steady_clock::time_point startTime;

ParkingNode::ParkingNode() : Node("robot_parking_node") {

    RCLCPP_INFO(get_logger(), "Parking Node Created");
    step = 0;
    MapCounter = 0;
    PATH.push_back(StartPoint);
    PATH.push_back(EndPoint);
    m_pub = create_publisher<Twist>("diffbot_amr/cmd_vel", 10);
    m_sub_head = create_subscription<LaserScan>(
            "diffbot_amr/scan", 10,
            std::bind(&ParkingNode::Lidar_Head_callback, this, std::placeholders::_1));
    m_sub_tail = create_subscription<LaserScan>(
            "diffbot_amr/scan2", 10,
            std::bind(&ParkingNode::Lidar_Tail_callback, this, std::placeholders::_1));
    m_sub_odom = create_subscription<Odometry>(
            "/diffbot_amr/odom", 10,
            std::bind(&ParkingNode::odom_callback, this, std::placeholders::_1));

    m_sub_obscom = create_subscription<ObsCom>(
            "obstacle_com",10,
            std::bind(&ParkingNode::com_callback, this, std::placeholders::_1));
}

void ParkingNode::Lidar_Head_callback(const LaserScan::SharedPtr msg)
{
    HeadLiDARFlag = true;
    Cluster.UpdateDynamicObstacle(msg->ranges, true);

}

void ParkingNode::Lidar_Tail_callback(const LaserScan::SharedPtr msg)
{
    TailLiDARFlag = true;
    Cluster.UpdateDynamicObstacle(msg->ranges, false);
}

void ParkingNode::odom_callback(const Odometry::SharedPtr msg)
{
    GetDuration();
    if(HeadLiDARFlag && TailLiDARFlag){
        HeadLiDARFlag = false;
        TailLiDARFlag = false;
        Cluster.ClusteringData();

        std::cout << "ABSTime: " << sharedMemory->duration << std::endl;
        std::cout << "ObsRealPosition: " << ObsRealPos.first << ", " << ObsRealPos.second << "\n";
        ClearPresentMatrix();// 장애물 인식한거 출력
//        if(!dynamicSharedMemory.LabelingArray.empty()){
//            dynamicSharedMemory.LabelingArray.front().second.first = int(ObsRealPos.first);
//            dynamicSharedMemory.LabelingArray.front().second.second = int(ObsRealPos.second);
//        }
        for(int i = 0; i < dynamicSharedMemory.LabelingArray.size(); i++){
            std::cout << "LabeledCenterPos[" << dynamicSharedMemory.LabelingArray[i].first.first <<"]: " << dynamicSharedMemory.LabelingArray[i].second.first << ", " << dynamicSharedMemory.LabelingArray[i].second.second << "\n";
        }
        ClearCostMap();
        int xAstar = int((sharedMemory->xpos+10)*5);
        int yAstar = int((sharedMemory->ypos+10)*5);
        coordinate AmrLoc = {xAstar,yAstar};
        PATH.front() = AmrLoc;
        if(abs(xAstar-PATH[1].first) < 1 && abs(yAstar-PATH[1].second) < 1)
        {
            PATH.erase(PATH.begin()+1);
        }
        if(PATH.size() == 1){
            std::cout << "Calculation Finished!";
            return;
        }
        ObsDec.ClassifyObsData();
        ObsDec.ObsPrediction();
////        ObsDec.ObsPredictionCurve();
        P_C.EvaluatePoint();
        ASTAR.startAstar(PATH);
        control_star_position(star_position(int((sharedMemory->xpos+10)*5), int((sharedMemory->ypos+10)*5)));
        while(!ASTAR.traj.empty())
        {
            ASTAR.traj.pop();
        }
//        P_C.PrintCostMap();
//        ObsDec.Pred_Print();
//        ASTAR.PrintMap(); // 맵 상의 경로 출력
    }
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

void ParkingNode::com_callback(const ObsCom::SharedPtr msg)
{
    ObsRealPos.first = msg->x;
    ObsRealPos.second = msg->y;
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
    if (abs(turn_offset) > 0.005) {
        sharedMemory->AMRVelocity = 1.0;
        m_twist_msg.linear.x = sharedMemory->AMRVelocity;
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
    sharedMemory->AMRVelocity = 0;
    sharedMemory->duration = 0;
    dynamicSharedMemory.coeff_data.clear();
    dynamicSharedMemory.obsLog.clear();
    dynamicSharedMemory.LabelingArray.clear();
    dynamicSharedMemory.coeff_sec_data.clear();
    for(int i = 0; i < GRID; i++){
        std::vector<double> temp;
        std::vector<int> temp2;
        for(int j = 0; j < GRID; j++){
            temp.push_back(0);
            temp2.push_back(0);
        }
        dynamicSharedMemory.CostMap.push_back(temp);
        dynamicSharedMemory.PresentMatrix.push_back(temp2);
    }
}

void StartSimulation()
{
    sharedMemory = (pSHM)malloc(sizeof(SHM));
    clearSharedMemory();
    startTime = std::chrono::steady_clock::now();
}

void ParkingNode::GetDuration(){
    auto endTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    sharedMemory->duration = static_cast<double>(elapsedTime.count());
    MapCounter++;
}

void ParkingNode::ClearCostMap(){
    for(int i = 0; i < GRID; i++){
        for(int j = 0; j < GRID; j++){
            dynamicSharedMemory.CostMap[i][j] = 0;
        }
    }
}
void ParkingNode::ClearPresentMatrix(){
    for(int i = 0; i < GRID; i++){
        for(int j = 0; j < GRID; j++){
            dynamicSharedMemory.PresentMatrix[i][j] = 0;
        }
    }
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