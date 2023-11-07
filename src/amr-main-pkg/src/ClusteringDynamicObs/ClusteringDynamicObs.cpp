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

Dcoordinate ClusteringDynamicObs::GazebotoGrid(Dcoordinate &Location) {
    Dcoordinate temp;
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
        temp = GazebotoGrid(temp);
        if (temp.first >= 0 && temp.first < 100 && temp.second >= 0 && temp.second < 100) {
            Point tempP;
            tempP.x = temp.first;
            tempP.y = temp.second;
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
Dcoordinate ClusteringDynamicObs::ObsCenterCalc(std::vector<Dcoordinate> Data) {
    double x1 = Data[0].first;
    double y1 = Data[0].second;
    double x2 = Data[1].first;
    double y2 = Data[1].second;
    double x3 = Data.back().first;
    double y3 = Data.back().second;
    double dx1 = x2-x1;
    double dx2 = x3-x1;
    double dy1 = y2-y1;
    double dy2 = y3-y1;
    double xCenter;
    double yCenter;
    Dcoordinate t;
    t = DotProduct(dx1, dx2, dy1, dy2);
    double length = t.first;
    double cosin = t.second;

    if(cosin > cos(PI/10)){ // 일자 상황
        std::cout << "일자\n";
        Dcoordinate a= GetMidPoint(x1,x3,y1,y3);;
        double xMid = a.first;
        double yMid = a.second;

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
        std::cout << "ㄴ자\n";
        Dcoordinate temp = GetMidPoint(x1, x3, y1, y3);
        xCenter = temp.first;
        yCenter = temp.second;
    }
    else { // ㄷ자 상황
        std::cout << "ㄷ자\n";
        double distance = std::sqrt(std::pow(dx2,2) + std::pow(dy2,2));
        Dcoordinate temp = GetMidPoint(x1, x3, y1, y3);
        xCenter = temp.first;
        yCenter = temp.second;
    }
    return std::make_pair(xCenter,yCenter);

}
void ClusteringDynamicObs::FindObsCenter(){
    int ID = ClusteredPoint.front().first;
    std::vector<Dcoordinate> temp;
    for(int i = 0; i < ClusteredPoint.size(); i++){
        if(ID == ClusteredPoint[i].first){
            temp.push_back(ClusteredPoint[i].second);
        }
        else{
            CenterPoint.push_back(std::make_pair(ID,ObsCenterCalc(temp)));
            temp.clear();
            ID = ClusteredPoint[i].first;
            temp.push_back(ClusteredPoint[i].second);
        }
    }
    CenterPoint.push_back(std::make_pair(ID,ObsCenterCalc(temp)));
}
Dcoordinate ClusteringDynamicObs::GetMidPoint(double x1, double x2, double y1, double y2){
    Dcoordinate temp;
    temp.first = (x1 + x2)/2;
    temp.second = (y1 + y2)/2;
    return temp;
}

Dcoordinate ClusteringDynamicObs::DotProduct(double dx1, double dx2, double dy1, double dy2) {
    double length = std::sqrt((std::pow(dx1,2) + std::pow(dy1,2)) + (std::pow(dx2,2)+std::pow(dy2,2)));
    double cosin = (dx1*dx2 + dy1*dy2)/(std::sqrt(std::pow(dx1,2) + std::pow(dy1,2))*std::sqrt(std::pow(dx2,2) + std::pow(dy2,2)));
    Dcoordinate temp;
    temp.first = length;
    temp. second = cosin;
    return temp;
}

void ClusteringDynamicObs::ClusteringData() {
    DBSCAN ds(MINIMUM_POINTS, EPSILON, Points);
    dynamicSharedMemory.LabelingArray.clear();
    ds.run();
    ClusteredPoint.clear();
    CenterPoint.clear();
    for(int i = 0; i < ds.m_points.size(); i++){
        Dcoordinate temp = std::make_pair(ds.m_points[i].x, ds.m_points[i].y);
        temp = GridtoGazebo(temp);
        temp = GlobaltoLocal(temp);
        if(ds.m_points[i].clusterID != -1){
            ClusteredPoint.push_back(std::make_pair(ds.m_points[i].clusterID,temp));
        }
    }
    Points.clear();
    if(!ClusteredPoint.empty()) FindObsCenter();
    for(int i = 0; i < CenterPoint.size(); i++) {
        CenterPoint[i].second = LocaltoGlobal(CenterPoint[i].second);
        CenterPoint[i].second = GazebotoGrid(CenterPoint[i].second);
    }
    if(LastObsPoint.empty()){
        for(int i = 0; i < CenterPoint.size(); i++) {
            dynamicSharedMemory.LabelingArray.push_back(std::make_pair(std::make_pair(CenterPoint[i].first, 0),
                                                                       std::make_pair(int(CenterPoint[i].second.first),
                                                                                      int(CenterPoint[i].second.second))));
            LastObsPoint.push_back(CenterPoint[i]);
        }
    }
    else{
        std::vector<Point> PPPoints;
        for(int i =0; i < LastObsPoint.size(); i++){
            Point tempP;
            tempP.x = LastObsPoint[i].second.first;
            tempP.y = LastObsPoint[i].second.second;
            tempP.z = 0;
            tempP.clusterID = LastObsPoint[i].first;
            PPPoints.push_back(tempP);
        }
        for(int i = 0; i < CenterPoint.size(); i++){
            Point tempP;
            tempP.x = CenterPoint[i].second.first;
            tempP.y = CenterPoint[i].second.second;
            tempP.z = 0;
            tempP.clusterID = UNCLASSIFIED;
            PPPoints.push_back(tempP);
        }
        DBSCAN dds(1, EPSILON, PPPoints);
        dds.run();
        for(int i = 0; i < dds.m_points.size(); i++){
            for(int j = 0; j < CenterPoint.size(); j++){
                if(dds.m_points[i].x == CenterPoint[j].second.first && dds.m_points[i].y == CenterPoint[j].second.second){
                    CenterPoint[j].first = dds.m_points[i].clusterID;
                }
            }
        }
        for(int i = 0; i < CenterPoint.size(); i++) {
            dynamicSharedMemory.LabelingArray.push_back(std::make_pair(std::make_pair(CenterPoint[i].first, 0),
                                                                       std::make_pair(int(CenterPoint[i].second.first),
                                                                                      int(CenterPoint[i].second.second))));
            LastObsPoint.push_back(CenterPoint[i]);
        }
    }
}
ClusteringDynamicObs::~ClusteringDynamicObs()
{

}