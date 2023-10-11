//
// Created by sangjun on 23. 9. 8.
//

#include "ObsDetection/PathChanger.hpp"


extern pSHM sharedMemory;
extern DSHM dynamicSharedMemory;

PathChanger::PathChanger()
{
}
double PathChanger::GetAngleCRadian(double a, double b, double c) {
    return std::acos((a * a + b * b - c * c) / (2 * a * b));
}
double PathChanger::GetDistance(coordinate p1, coordinate p2) {
    return std::sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

void PathChanger::MadeCostMap(coordinate &p) {
    for(int i = p.first - SafeDistance; i <= p.first + SafeDistance; i++){
        for(int j = p.second - SafeDistance; j <= p.second + SafeDistance; j++){
            if(i >= GRID || i < 0 || j >= GRID || j < 0) continue;
            double dist = GetDistance(p,std::make_pair(i,j));
            if(dist <= SafeDistance){
                dynamicSharedMemory.CostMap[i][j] = 100;
            }
        }
    }
}

void PathChanger::EvaluatePoint() {
    int xAstar = int((sharedMemory->xpos+10)*5);
    int yAstar = int((sharedMemory->ypos+10)*5);
    coordinate AmrLoc = std::make_pair(xAstar,yAstar);
    for(int i = 0; i < dynamicSharedMemory.obsLog.size(); i++){
        for(int j = 0; j < dynamicSharedMemory.obsLog[i].obsPredLoc.size(); j++){
            coordinate p = dynamicSharedMemory.obsLog[i].obsPredLoc[j].second;
            double time = sharedMemory->duration + GetDistance(AmrLoc,p)/sharedMemory->AMRVelocity;
            double timeinterval = dynamicSharedMemory.obsLog[i].obsPredLoc[j].first - time;
            double AMRSafeTime = SafeDistance/sharedMemory->AMRVelocity;
            if(timeinterval <= AMRSafeTime){
                MadeCostMap(p);
            }
        }
    }
}

void PathChanger::PrintCostMap() {
    for(int i = 0 ; i < GRID; i++){
        for(int j = 0; j < GRID; j++){
            std::cout << dynamicSharedMemory.CostMap[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

PathChanger::~PathChanger()
{

}