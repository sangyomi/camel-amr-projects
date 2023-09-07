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
public:
    std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> LabelingArray;
    double timer_cycle;
    ClusteringDynamicObs();
    void UpdateDynamicObstacle(std::vector<float> &scanarray, std::vector<std::vector<int>> &Mapmatrix, double heading, double xpos, double ypos, int MapCounter);
    void ClusteringDynamicObstacle(int xPos, int yPos);
    void CheckObstacle(int i, int j, int ChangeObstacle, int& SizeCount, std::vector<std::pair<int, int>>& ClusteringInfo);
    void ConnectObs(int avgX, int avgY);
    void PrintMap();
    ~ClusteringDynamicObs();
};


#endif //CAMEL_AMR_PROJECTS_V1_CLUSTERINGDYNAMICOBS_HPP