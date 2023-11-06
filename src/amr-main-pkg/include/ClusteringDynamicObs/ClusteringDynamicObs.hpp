//
// Created by sangjun on 23. 8. 29.
//

#ifndef CAMEL_AMR_PROJECTS_V1_CLUSTERINGDYNAMICOBS_HPP
#define CAMEL_AMR_PROJECTS_V1_CLUSTERINGDYNAMICOBS_HPP

#include <bits/stdc++.h>
#include <memory>
#include <vector>
#include <tuple>
#include <cmath>
#include <iostream>
#include <ctime>
#include <chrono>
#include <time.h>
#include "Variables/SharedMemory.h"
#include "ClusteringDynamicObs/DBSCAN.hpp"

using Time = std::chrono::high_resolution_clock::time_point;

class ClusteringDynamicObs {
private:
    int x_spot[720];
    int y_spot[720];
    std::vector<std::vector<int>> SavedMatrix;
    std::vector<std::vector<int>> DynamicMatrix;
    std::vector<std::vector<int>> ClusteringMatrix;
    std::vector<int> LabelingStack;
    int ObstacleLabel;
    clock_t timer_start;
    clock_t timer_end;
    void ClearClustringMatrix();
    std::vector<Point> Points;
    std::vector<std::vector<Dcoordinate>> ClusteredPoint;
    std::vector<Dcoordinate> CenterPoint;
    Dcoordinate ProcessLidarRawtoLocal(float &scannedlength, int &numofScan, int iter, bool ID);
    Dcoordinate LocaltoGlobal(Dcoordinate &LocalPos);
    coordinate GazebotoGrid(Dcoordinate &Location);
    Dcoordinate GridtoGazebo(Dcoordinate &Location);
    Dcoordinate GlobaltoLocal(Dcoordinate &GlobalPos);
    void FindObsCenter();
    Dcoordinate DotProduct(double dx1, double dx2, double dy1, double dy2);
    Dcoordinate GetMidPoint(double x1, double x2, double y1, double y2);
public:
    double timer_cycle;
    ClusteringDynamicObs();
    void UpdateDynamicObstacle(std::vector<float> &scanarray,bool LiDARID);
    void ClusteringDynamicObstacle(int xPos, int yPos);
    void CheckObstacle(int i, int j, int ChangeObstacle, int& SizeCount, std::vector<std::pair<int, int>>& ClusteringInfo);
    void ConnectObs(int avgX, int avgY);
    void PrintMap();
    void ClusteringData();
    ~ClusteringDynamicObs();
};


#endif //CAMEL_AMR_PROJECTS_V1_CLUSTERINGDYNAMICOBS_HPP