//
// Created by sangjun on 23. 8. 29.
//

#include "ClusteringDynamicObs/ClusteringDynamicObs.hpp"
#define D2R 0.017453293
#define AMRX 0.325
#define AMRY 0.455
#define MINIMUM_POINTS 4     // minimum number of cluster
#define EPSILON (2.5*2.5)

extern pSHM sharedMemory;
extern DSHM dynamicSharedMemory;

ClusteringDynamicObs::ClusteringDynamicObs()
        : SavedMatrix(GRID, std::vector<int>(GRID, 0)),
          DynamicMatrix(GRID, std::vector<int>(GRID, 0)),
          ClusteringMatrix(GRID, std::vector<int>(GRID, 0))
{
    ObstacleLabel = 4;
}

Dcoordinate ClusteringDynamicObs::ProcessLidarRawtoLocal(float &scannedlength, int &numofScan, int iter, bool ID){
    const int LiDAR = 270;
    double theta = double(LiDAR)/double(numofScan) * iter * D2R;

    double XPos;
    double YPos;
    if(ID){ // Head_LiDAR
        XPos = scannedlength * sin(theta)+AMRX;
        YPos = -1 * scannedlength * cos(theta)+AMRY;
    }
    else{ // Tail_LiDAR
        XPos = -1 * scannedlength * sin(theta) - AMRX;
        YPos = scannedlength * cos(theta) - AMRY;
    }
    Dcoordinate LocalPos = std::make_pair(XPos, YPos);
    return LocalPos;
}
Dcoordinate ClusteringDynamicObs::LocaltoGlobal(Dcoordinate &LocalPos) {
    double theta = PI/2 - sharedMemory->heading;
    double XPos = LocalPos.first;
    double YPos = LocalPos.second;
    double globalXPos = XPos * cos(theta) + YPos * sin(theta) + sharedMemory->xpos;
    double globalYPos = -XPos * sin(theta) + YPos * cos(theta) + sharedMemory->ypos;
    Dcoordinate GlobalPos = std::make_pair(globalXPos,globalYPos);
    return GlobalPos;
}

coordinate ClusteringDynamicObs::GazebotoGrid(Dcoordinate &Location) {
    coordinate temp;
    temp.first = Location.first*5 + 50;
    temp.second = Location.second*5 + 50;
    return temp;
}

void ClusteringDynamicObs::ClearClustringMatrix() {
    for(int i = 0; i < GRID; i++){
        for(int j = 0; j < GRID; j++){
            ClusteringMatrix[i][j] = 0;
        }
    }
}

void ClusteringDynamicObs::UpdateDynamicObstacle(std::vector<float> &scanarray, bool LiDARID)
{
    int numofScan = scanarray.size();
    for (int iter = 0 ; iter < numofScan ; iter++) {
        Dcoordinate temp = ProcessLidarRawtoLocal(scanarray[iter], numofScan, iter, LiDARID);
        temp = LocaltoGlobal(temp);
        coordinate temp2 = GazebotoGrid(temp);
        if (temp2.first >= 0 && temp2.first < 100 && temp2.second >= 0 && temp2.second < 100) {
            Point tempP;
            tempP.x = temp2.first;
            tempP.y = temp2.second;
            tempP.z = 0;
            tempP.clusterID = UNCLASSIFIED;
            Points.push_back(tempP);
        }
    }
}

Dcoordinate ClusteringDynamicObs::GridtoGazebo(Dcoordinate &Location) {
    Dcoordinate temp;
    temp.first = (Location.first - 50)/5;
    temp.second = (Location.second- 50)/5;
    return temp;
}

Dcoordinate ClusteringDynamicObs::GlobaltoLocal(Dcoordinate &GlobalPos) {
    double theta = -1*(PI/2 - sharedMemory->heading);
    double XPos = GlobalPos.first;
    double YPos = GlobalPos.second;
    double LocalXPos = XPos * cos(theta) + YPos * sin(theta) + sharedMemory->xpos;
    double LocalYPos = -XPos * sin(theta) + YPos * cos(theta) + sharedMemory->ypos;
    Dcoordinate LocalPos = std::make_pair(LocalXPos,LocalYPos);
    return LocalPos;
}

void ClusteringDynamicObs::ClusteringData() {
    DBSCAN ds(MINIMUM_POINTS, EPSILON, Points);
    ds.run();
    for(int i = 0; i < ds.m_points.size(); i++){
        Dcoordinate temp = std::make_pair(ds.m_points[i].x, ds.m_points[i].y);
        temp = GazebotoGrid(temp);
        temp = GlobaltoLocal(temp);
        if(ds.m_points[i].clusterID != -1){
            ClusteredPoint[ds.m_points[i].clusterID].push_back(temp);
        }
    }
    Points.clear();
//    FindObsCenter();
//    for(int i = 0; i < CenterPoint.size(); i++){
//        CenterPoint[i] = LocaltoGlobal(CenterPoint[i]);
//        CenterPoint[i] = GazebotoGrid(CenterPoint[i]);
//        std::cout << "Clustered_Center_point: " << CenterPoint[i].first << ", " << CenterPoint[i].second << "\n";
//    }
}
void ClusteringDynamicObs::FindObsCenter(){
    for(int i = 0; i < ClusteredPoint.size();i++){
        double x1 = ClusteredPoint[i].front().first;
        double y1 = ClusteredPoint[i].front().second;
        double x2 = ClusteredPoint[i][1].first;
        double y2 = ClusteredPoint[i][1].second;
        double x3 = ClusteredPoint[i].back().first;
        double y3 = ClusteredPoint[i].back().second;
        double dx1 = x2-x1;
        double dx2 = x3-x1;
        double dy1 = y2-y1;
        double dy2 = y3-y1;
        double length;
        double cosin;
        double xCenter;
        double yCenter;
        std::make_pair(length, cosin) = DotProduct(dx1, dx2, dy1, dy2);
        if(cosin > cos(PI/10)){ // 일자 상황
            double xMid;
            double yMid;
            std::make_pair(xMid, yMid) = GetMidPoint(x1,x3,y1,y3);
            double distance = std::sqrt(std::pow(xMid,2) + std::pow(yMid,2));
            if(std::abs(length - 0.8) < std::abs(length-1.1)){
                xCenter = xMid *((distance + 0.55)/distance);
                yCenter = yMid *((distance + 0.55)/distance);
            }
            else{
                xCenter = xMid *((distance + 0.4)/distance);
                yCenter = yMid *((distance + 0.4)/distance);
            }

        }
        else if(cosin > cos(PI/3)){ // ㄴ자 상황
            std::make_pair(xCenter,yCenter) = GetMidPoint(x1, x3, y1, y3);
        }

        else { // ㄷ자 상황
            double distance = std::sqrt(std::pow(dx2,2) + std::pow(dy2,2));
            std::make_pair(xCenter,yCenter) = GetMidPoint(x1, x3, y1, y3);
        }
        CenterPoint[i] = std::make_pair(xCenter,yCenter);
    }
}
Dcoordinate ClusteringDynamicObs::GetMidPoint(double x1, double x2, double y1, double y2){
    Dcoordinate temp;
    temp.first = (x1 + x2)/2;
    temp.second = (y1 + y2)/2;
    return temp;
}

Dcoordinate ClusteringDynamicObs::DotProduct(double dx1, double dx2, double dy1, double dy2) {
    double length = std::sqrt((std::pow(dx1,2) + std::pow(dy1,2)) + (std::pow(dx2,2)+std::pow(dy2,2)));
    double cosin = (dx1*dx2 + dy1*dy2)/length;
    return std::make_pair(length,cosin);
}

void ClusteringDynamicObs::ClusteringDynamicObstacle(int xPos, int yPos)
{
    int ChangeObstacle = 5;
    for (int i = 0; i < GRID; ++i)
    {
        for (int j = 0; j < GRID; ++j)
        {
            if(DynamicMatrix[i][j] == 1)
            {
                int SizeCount = 0;
                std::vector<std::pair<int, int>> ClusteringInfo;

                CheckObstacle(i,j,ChangeObstacle,SizeCount, ClusteringInfo);

                if (SizeCount > 5)
                {
                    int sumX = 0;
                    int sumY = 0;
                    int numPoints = ClusteringInfo.size();

                    for (const std::pair<int, int>& point : ClusteringInfo) {
                        sumX += point.first;
                        sumY += point.second;
                    }
                    if (numPoints > 0) {
                        sumX = sumX / numPoints;
                        sumY = sumY / numPoints;
                    }

                    double rad = std::atan2(sumY - yPos, sumX - xPos);

                    sumX = sumX + int((SizeCount * 0.01)*(std::cos(rad)));
                    sumY = sumY + int((SizeCount * 0.01)*(std::sin(rad)));

                    ConnectObs(sumX, sumY);
                }
            }
        }
    }
    for (int i = 0 ; i < LabelingStack.size() ; i++)
    {
        if(LabelingStack[i] == dynamicSharedMemory.LabelingArray[i].first.second)
        {
            dynamicSharedMemory.LabelingArray.erase(dynamicSharedMemory.LabelingArray.begin() + i);
        }
    }
    LabelingStack.clear();
    for (int i = 0 ; i < dynamicSharedMemory.LabelingArray.size() ; i++)
    {
        LabelingStack.push_back(dynamicSharedMemory.LabelingArray[i].first.second);
    }
}

void ClusteringDynamicObs::CheckObstacle(int i, int j, int ChangeObstacle, int& SizeCount, std::vector<std::pair<int, int>>& ClusteringInfo)
{
    if(( 0<=i && i<GRID ) && ( 0<=j && j<GRID ) && (DynamicMatrix[i][j] == 1))
    {
        SizeCount++;
        DynamicMatrix[i][j] = ChangeObstacle;
        ClusteringInfo.push_back(std::make_pair(i,j));
        CheckObstacle(i-1,j,ChangeObstacle,SizeCount,ClusteringInfo);
        CheckObstacle(i+1,j,ChangeObstacle,SizeCount,ClusteringInfo);
        CheckObstacle(i,j-1,ChangeObstacle,SizeCount,ClusteringInfo);
        CheckObstacle(i,j+1,ChangeObstacle,SizeCount,ClusteringInfo);
    }
    else
    {
        return;
    }
}

void ClusteringDynamicObs::ConnectObs(int avgX, int avgY)
{
    double distance = 7;
    int temp = -1;

    for (int i = 0 ; i < dynamicSharedMemory.LabelingArray.size() ; i++)
    {
        int t = std::sqrt(std::pow(avgX-dynamicSharedMemory.LabelingArray[i].second.first,2) + std::pow(avgY-dynamicSharedMemory.LabelingArray[i].second.second,2));

        if(distance > t)
        {
            distance = t;
            ClusteringMatrix[avgX][avgY] = dynamicSharedMemory.LabelingArray[i].first.first;
            temp = i;
        }
    }

    if (temp != -1) // 기존 노드 업데이트
    {
        dynamicSharedMemory.LabelingArray[temp] = std::make_pair(std::make_pair(dynamicSharedMemory.LabelingArray[temp].first.first, dynamicSharedMemory.
                LabelingArray[temp].first.second + 1), std::make_pair(avgX, avgY));
    }
    else // 새로운 노드 생성
    {
        ObstacleLabel++;
        ClusteringMatrix[avgX][avgY] = ObstacleLabel;
        dynamicSharedMemory.LabelingArray.push_back(std::make_pair(std::make_pair(ObstacleLabel, 1), std::make_pair(avgX, avgY)));
    }
}

void ClusteringDynamicObs::PrintMap()
{
    std::cout<< "\n";
    for (int i = 0; i < GRID; ++i) {
        for (int j = 0; j < GRID; ++j) {
            std::cout << ClusteringMatrix[i][j];
//            std::cout << SavedMatrix[i][j];
//            std::cout << DynamicMatrix[i][j];
        }
        std::cout << '\n';
    }
}

ClusteringDynamicObs::~ClusteringDynamicObs()
{

}