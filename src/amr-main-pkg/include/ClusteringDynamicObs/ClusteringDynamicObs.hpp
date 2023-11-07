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
    struct ClustPoint{
        std::vector<Dcoordinate> Clusterpoint;
    };
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
    std::vector<std::pair<int,Dcoordinate>> ClusteredPoint;
    std::vector<std::pair<int,Dcoordinate>> CenterPoint;
    std::vector<std::pair<int,Dcoordinate>> LastObsPoint;
    Dcoordinate ProcessLidarRawtoLocal(float &scannedlength, int &numofScan, int iter, bool ID);
    Dcoordinate LocaltoGlobal(Dcoordinate &LocalPos);
    Dcoordinate GazebotoGrid(Dcoordinate &Location);
    Dcoordinate GridtoGazebo(Dcoordinate &Location);
    Dcoordinate GlobaltoLocal(Dcoordinate &GlobalPos);
    Dcoordinate ObsCenterCalc(std::vector<Dcoordinate> Data);
    void FindObsCenter();
    Dcoordinate DotProduct(double dx1, double dx2, double dy1, double dy2);
    Dcoordinate GetMidPoint(double x1, double x2, double y1, double y2);
public:
    double timer_cycle;
    ClusteringDynamicObs();
    void UpdateDynamicObstacle(std::vector<float> &scanarray,bool LiDARID);
    void ClusteringData();
    ~ClusteringDynamicObs();
};


#endif //CAMEL_AMR_PROJECTS_V1_CLUSTERINGDYNAMICOBS_HPP