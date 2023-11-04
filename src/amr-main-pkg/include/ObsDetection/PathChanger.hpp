//
// Created by sangjun on 23. 9. 8.
//

#ifndef CAMEL_AMR_PROJECTS_SWEETYS_PATHCHANGER_HPP
#define CAMEL_AMR_PROJECTS_SWEETYS_PATHCHANGER_HPP


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include "Variables/Variable.hpp"
#include "Variables/mapinfo.hpp"
#include "Variables/SharedMemory.h"

class PathChanger {
private:
    struct SafeLoc{
        coordinate alterpoint;
        coordinate destination;
        int check;
        double time;
    };
    const int AmrSafeArea = 3;
    const int ObsSafeArea = 3;
    double GetDistance(coordinate p1, coordinate p2);
    double GetAngleCRadian(double a, double b, double c);
    void MadeCostMap(coordinate &p, double loss);
public:
    PathChanger();
    void EvaluatePoint();
    ~PathChanger();
    int SafeDistance = AmrSafeArea + ObsSafeArea + 4;
    std::vector<coordinate> SafeLocation;
    void PrintCostMap();
};


#endif //CAMEL_AMR_PROJECTS_SWEETYS_PATHCHANGER_HPP