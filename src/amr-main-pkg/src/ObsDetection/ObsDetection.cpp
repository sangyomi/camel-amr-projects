//
// Created by 최영수 on 2023/08/01.
//
#include "ObsDetection/ObsDetection.hpp"

/// Private Function
bool ObsDetection::isObstacle(int i, int j, int map[][100]) {
//    bool test2 = (map[i][j] == 6) ? 1 : 0;
    return (map[i][j] == 6) ? 1 : 0;
}
void ObsDetection::updateGradient(){
    if (rs.next_pos.first == rs.present_pos.first) rs.grad = rs.dy * 999999;
    else rs.grad = rs.dy / rs.dx;
}

bool ObsDetection::isObstacleInSlope(int i, int j){
    if (rs.grad > 0) {
//        bool test1 = (j > -1 / grad * (i - present_pos.first) + present_pos.second);
        return (j > -1 / rs.grad * (i - rs.present_pos.first) + rs.present_pos.second);
    }
    if (rs.grad == 0) {
        if ((rs.dy > 0 && j < rs.present_pos.second) || (rs.dy < 0 && j > rs.present_pos.second))
            return false;
    }
    return (j < -1 / rs.grad * (i - rs.present_pos.first) + rs.present_pos.second);
}

void ObsDetection::New_labeling(coordinate &obs_loc) {
    labeled_obs[labeling].pos.push(obs_loc);
    labeled_obs[labeling].velocity = 0;
    labeled_obs[labeling].dir = obs_loc;
    labeling++;
}

/// Public Function
void ObsDetection::SetSensorRange(int SensorRange) {
    rs.SensorRange = SensorRange;
}

void ObsDetection::loadRobotStatus(coordinate pre, coordinate nex) {
    rs.present_pos = pre;
    rs.next_pos = nex;
    rs.dy = rs.next_pos.second - rs.present_pos.second;
    rs.dx = rs.next_pos.first - rs.present_pos.first;
    updateGradient();
}

int ObsDetection::isObstacleDetected(int map[][100], coordinate &mapsize) {
    int detect_count = 0;
    for (int i = rs.present_pos.first - rs.SensorRange; i <= rs.present_pos.first + rs.SensorRange; ++i) {
        for (int j = rs.present_pos.second - rs.SensorRange; j <= rs.present_pos.second + rs.SensorRange; ++j) {
            if (MapFunction::isOutofRange(i,j,mapsize)) continue; /// detection area should be in the map,,,,
            if(isObstacleInSlope(i, j) && (isObstacle(i, j, map) == 1)) {
                detect_count++;
                detected_obs_loc.push(std::make_pair(i,j));
            }
        }
    }
    return detect_count;
}

coordinate ObsDetection::GetDetectedObsLoc() {
    coordinate a = detected_obs_loc.top();
    detected_obs_loc.pop();
    return a;
}
void ObsDetection::SetNumObstacle(int num_obs){
    this->num_obs = num_obs;
}

bool ObsDetection::SetObsTraj(coordinate obs_loc) {
    if(labeling == 0){
        New_labeling(obs_loc);
    }
    else{
        bool check = false;
        for(int i = 0; i < labeling; i++){
            coordinate old = labeled_obs[i].pos.top();
            if(abs(obs_loc.first-old.first) <= 1 && abs(obs_loc.second-old.second) <= 1){
                labeled_obs[i].pos.push(obs_loc);
                check = true;
                break;
            }

        }
        if(!check)
            New_labeling(obs_loc);
    }

    return true;
}

int ObsDetection::GetLabelData(){
    return labeling;
}
std::stack<coordinate> ObsDetection::GetObsTraj(int i){
    return labeled_obs[i].pos;
}
