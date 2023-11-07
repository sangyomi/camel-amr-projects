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

void PathChanger::MadeCostMap(coordinate &p, double loss) {
    int ChangeAreaLength = SafeDistance + int(loss*3);
    for(int i = p.first - ChangeAreaLength; i <= p.first + ChangeAreaLength; i++){
        for(int j = p.second - ChangeAreaLength; j <= p.second + ChangeAreaLength; j++){
            if(i >= GRID || i < 0 || j >= GRID || j < 0) continue;
            double dist = GetDistance(p,std::make_pair(i,j));
            int cost;
            if(dist == 0) cost = 1200;
            else if(dist <= SafeDistance) cost = 1000/dist;
            else if(dist <= ChangeAreaLength) cost = loss*3 / (dist-SafeDistance)+1;
            else cost = 0;
            if(cost == 1) cost = 0;
            if(dynamicSharedMemory.CostMap[i][j] == 0){
                dynamicSharedMemory.CostMap[i][j] = cost;
            }
            else{
                if(dynamicSharedMemory.CostMap[i][j] < cost){
                    dynamicSharedMemory.CostMap[i][j] = cost;
                }
            }
        }
    }
}

void PathChanger::EvaluatePoint() {
    int xAstar = int((sharedMemory->xpos+10)*5);
    int yAstar = int((sharedMemory->ypos+10)*5);
    coordinate AmrLoc = std::make_pair(xAstar,yAstar);
    for(int i = 0; i < dynamicSharedMemory.obsLog.size(); i++){
        if(dynamicSharedMemory.obsLog[i].obsPredLoc.empty()){
            MadeCostMap(dynamicSharedMemory.obsLog[i].obsLocationLog.back().second, dynamicSharedMemory.obsLog[i].loss);
        }
        for(int j = 0; j < dynamicSharedMemory.obsLog[i].obsPredLoc.size(); j++){
            coordinate p = dynamicSharedMemory.obsLog[i].obsPredLoc[j].second;
            double timeinterval = dynamicSharedMemory.obsLog[i].obsPredLoc[j].first - sharedMemory->duration;
            double distance = GetDistance(p,AmrLoc);
            if(abs(distance - timeinterval/1000 * sharedMemory->AMRVelocity) <= SafeDistance + 5){
                MadeCostMap(p, dynamicSharedMemory.obsLog[i].loss);
            }
            if(dynamicSharedMemory.obsLog[i].loss >= 3){
                MadeCostMap(dynamicSharedMemory.obsLog[i].obsLocationLog.back().second, dynamicSharedMemory.obsLog[i].loss);
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