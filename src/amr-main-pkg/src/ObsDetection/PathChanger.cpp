//
// Created by sangjun on 23. 9. 8.
//

#include "ObsDetection/PathChanger.hpp"

PathChanger::PathChanger()
{
}
double PathChanger::GetAngleCRadian(double a, double b, double c) {
    return std::acos((a * a + b * b - c * c) / (2 * a * b));
}
coordinate PathChanger::MakeAlterPoint(coordinate AmrLoc, coordinate ColPredictedPoint, coordinate ObsSamplePoint){
    int a = ColPredictedPoint.first - ObsSamplePoint.first;
    int b = ColPredictedPoint.second - ObsSamplePoint.second;
    int c = -a*ColPredictedPoint.first -b*ColPredictedPoint.second;
    int x1 = ObsSamplePoint.first;
    int y1 = ObsSamplePoint.second;
    coordinate returnValue;
    int xLoc;
    int yLoc;
    if(a == 0 && b == 0){
        xLoc = -1;
        yLoc = -1;
    }
    else if(a != 0 && b==0){
        xLoc = ObsSamplePoint.first;
        int yLoc1 = ObsSamplePoint.second+SafeDistance;
        int yLoc2 = ObsSamplePoint.second-SafeDistance;
        double dist1 = GetDistance(std::make_pair(xLoc,yLoc1),AmrLoc);
        double dist2 = GetDistance(std::make_pair(xLoc,yLoc2),AmrLoc);
        if(dist1 > dist2) yLoc = yLoc2;
        else yLoc = yLoc1;
    }
    else if(a == 0 && b != 0){
        int xLoc1 = ObsSamplePoint.first-SafeDistance;
        int xLoc2 = ObsSamplePoint.first+SafeDistance;
        yLoc = ObsSamplePoint.second;
        double dist1 = GetDistance(std::make_pair(xLoc1,yLoc),AmrLoc);
        double dist2 = GetDistance(std::make_pair(xLoc2,yLoc),AmrLoc);
        if(dist1 > dist2) xLoc = xLoc2;
        else xLoc = xLoc1;
    }
    else{
        double a1 = 1 + (a/b)*(a/b);
        double b1 = -2*x1 + 2*a/b*(c/b + y1);
        double c1 = x1*x1 + (c/b+y1)*(c/b+y1) - SafeDistance*SafeDistance;
        double xLoc1 = (-b1 + std::sqrt(b1*b1 -4*a1*c1))/(2*a1);
        double yLoc1 = -a/b*xLoc1-c/b;
        double xLoc2 = (-b1 - std::sqrt(b1*b1 -4*a1*c1))/(2*a1);
        double yLoc2 = -a/b*xLoc2-c/b;
        double dist1 = GetDistance(std::make_pair(xLoc1,yLoc1),AmrLoc);
        double dist2 = GetDistance(std::make_pair(xLoc2,yLoc2),AmrLoc);
        if(dist1 > dist2) {
            xLoc = int(xLoc2);
            yLoc = int(yLoc2);
        }
        else {
            xLoc = int(xLoc1);
            yLoc = int(yLoc1);
        }
    }

    returnValue = std::make_pair(xLoc,yLoc);
    return returnValue;
}
double PathChanger::GetDistance(coordinate p1, coordinate p2) {
    return std::sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}
int PathChanger::CollisionPrediction(std::vector<coordinate> &AmrTraj, std::vector<coordinate> &ObsTraj){
    int sizeA = AmrTraj.size();
    int sizeO = ObsTraj.size();
    int minsize = std::min(sizeA,sizeO);
    for (int i = 0 ; i < minsize ; i++){
        double distance = GetDistance(AmrTraj[i],ObsTraj[i]);
        if(distance + 2 <= SafeDistance) return i;
    }
    return -1;
}
void PathChanger::GetSafeLoc(PathChangeData PCD, double AbsTime){

    std::vector<SafeLoc> newTraj;
    newTraj.clear();
    SafeLocation.clear();
    coordinate alternativePoint;
    for(int i = 0 ; i < PCD.ObsTrajSample.size(); i++){
        double ColDist = GetDistance(PCD.AmrLoc, PCD.ColPredictedPoint);
        double distance = GetDistance(PCD.AmrLoc, PCD.ObsTrajSample[i]);
        double AmrArrivalTime;
        int Check; // 최단거리냐, 돌아서가냐.
        if(ColDist > distance){
            AmrArrivalTime = (distance+SafeDistance)/(PCD.AmrVel*5/1000) + AbsTime;
            Check = 0;
        }
        else{
            alternativePoint = MakeAlterPoint(PCD.AmrLoc,PCD.ColPredictedPoint,PCD.ObsTrajSample[i]);
            if(alternativePoint.first == -1 && alternativePoint.second == -1) continue;
            double newdistance = GetDistance(PCD.AmrLoc, alternativePoint) + GetDistance(alternativePoint,PCD.ObsTrajSample[i]);
            AmrArrivalTime = (newdistance+SafeDistance)/(PCD.AmrVel*5/1000) + AbsTime;
            Check = 1;
        }

        double ObsXLoc = PCD.ObsCoeffData.first.first + PCD.ObsCoeffData.first.second * AmrArrivalTime;
        double ObsYLoc = PCD.ObsCoeffData.second.first + PCD.ObsCoeffData.second.second * AmrArrivalTime;

        if(ObsXLoc > 100 || ObsYLoc < 0 || ObsYLoc > 100 || ObsXLoc < 0) continue;

        double FutureDistance = GetDistance(std::make_pair(ObsXLoc,ObsYLoc),PCD.ObsTrajSample[i]);
        if(FutureDistance >= SafeDistance + 4){
            SafeLoc temp;
            temp.time = AmrArrivalTime;
            temp.destination = PCD.ObsTrajSample[i];
            temp.check = Check;
            if(Check == 1) temp.alterpoint = alternativePoint;
            else temp.alterpoint = std::make_pair(0,0);
            newTraj.push_back(temp);
        }
    }
    int Time = 10000000;
    int location;
    if(!newTraj.empty()){
        for(int i = 0; i <newTraj.size();i++){
            if(newTraj[i].time < Time) {
                location = i;
                Time = newTraj[i].time;
            }
            std::cout <<"ArrivalTime: "<< newTraj[i].time << "[ms], location: (" << newTraj[i].destination.first << ", " << newTraj[i].destination.second << ")";
            if(newTraj[i].check == 1){
                std::cout <<", Through ("<< newTraj[i].alterpoint.first << ", " << newTraj[i].alterpoint.second <<")\n";
            }
            else std::cout << "\n";
        }
        SafeLoc temp = newTraj[location];
        if(temp.check == 0){
            int xplus = temp.destination.first - PCD.AmrLoc.first;
            int yplus = temp.destination.second - PCD.AmrLoc.second;
            coordinate additional_dest = std::make_pair(temp.destination.first + xplus, temp.destination.second+yplus);
            SafeLocation.push_back(temp.destination);
//            if(xplus !=0 || yplus !=0){
//                SafeLocation.push_back(additional_dest);
//            }

        }
        else{
            int xplus = temp.destination.first - temp.alterpoint.first;
            int yplus = temp.destination.second - temp.alterpoint.second;
            coordinate additional_dest = std::make_pair(temp.destination.first + xplus, temp.destination.second+yplus);
            SafeLocation.push_back(temp.alterpoint);
            SafeLocation.push_back(temp.destination);
//            if(xplus !=0 || yplus !=0){
//                SafeLocation.push_back(additional_dest);
//            }
        }
    }
}

PathChanger::~PathChanger()
{

}