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

void ObsDetection::New_labeling(coordinate &obs_loc, int &step) {
    labeled_obs[labeling].pos.push(obs_loc);
    labeled_obs[labeling].step.push(step);
    labeling++;
}

void ObsDetection::SaveObsTraj(coordinate obs_loc, int &step) {
    if (labeling == 0) {
        detected_obs_num.push(labeling);
        New_labeling(obs_loc, step);
    } else {
        bool check = false;
        for (int i = 0; i < labeling; i++) {
            coordinate old = labeled_obs[i].pos.top();
            if (abs(obs_loc.first - old.first) <= 1 && abs(obs_loc.second - old.second) <= 1) {
                detected_obs_num.push(i);
                labeled_obs[i].pos.push(obs_loc);
                labeled_obs[i].step.push(step);
                labeled_obs[i].velocity = 1;
                labeled_obs[i].dir.first = obs_loc.first - old.first;
                labeled_obs[i].dir.second = obs_loc.second - old.second;
                check = true;
                break;
            }

        }
        if (!check) {
            detected_obs_num.push(labeling);
            New_labeling(obs_loc, step);
        }
    }
}

coordinate ObsDetection::GetObsNextPos(int &i, int &iter) {
    auto NextPos = labeled_obs[i].pos.top();
    NextPos.first = NextPos.first + labeled_obs[i].dir.first*labeled_obs[i].velocity*iter;
    NextPos.second = NextPos.second + labeled_obs[i].dir.second*labeled_obs[i].velocity*iter;
    return NextPos;
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

int ObsDetection::isObstacleDetected(int map[][100], coordinate &mapsize, int &step) {
    int detect_count = 0;
    for (int i = rs.present_pos.first - rs.SensorRange; i <= rs.present_pos.first + rs.SensorRange; ++i) {
        for (int j = rs.present_pos.second - rs.SensorRange; j <= rs.present_pos.second + rs.SensorRange; ++j) {
            if (MapFunction::isOutofRange(i, j, mapsize)) continue; /// detection area should be in the map,,,,
            if (isObstacleInSlope(i, j) && (isObstacle(i, j, map) == 1)) {
                detect_count++;
                SaveObsTraj(std::make_pair(i, j), step);
            }
        }
    }
    return detect_count;
}

int ObsDetection::GetDetectedObsNum() {
    int num = detected_obs_num.top();
    detected_obs_num.pop();
    return num;
}
void ObsDetection::SetNumObstacle(int num_obs){
    this->num_obs = num_obs;
}

int ObsDetection::GetLabelData() {
    return labeling;
}


void ObsDetection::CollisionDetection(std::stack<coordinate> AMR_Traj){
    auto SAVE_DATA = AMR_Traj;
    while(!detected_obs_num.empty()){
        int obsNum = GetDetectedObsNum();
        for(int i = 1; i <= 5; i++){
            auto obsPos = GetObsNextPos(obsNum,i);
            auto amr_next_pos = AMR_Traj.top();

            if(obsPos == amr_next_pos){
                std::cout <<"Obstacle label " << obsNum << "가 " << i << "초 이후 충돌합니다!!\n";
                std::cout << "Predicted Obstacle Trajectory: ";
                for(int j = 1; j <= i; j++){
                    auto obsFuturePos = GetObsNextPos(obsNum, j);
                    std::cout << "("<< obsFuturePos.first << ", " << obsFuturePos.second << ")";
                    if(j!=i) std::cout <<", ";
                }
                std::cout << "\nAMR Trajectory: ";
                for(int j = 1; j <= i; j++){
                    std::cout << "("<< SAVE_DATA.top().first << ", " << SAVE_DATA.top().second << ")";
                    if(j!=i) std::cout <<", ";
                    SAVE_DATA.pop();
                }
                std::cout << "\n";
            }
            AMR_Traj.pop();
        }
    }
}
//현재