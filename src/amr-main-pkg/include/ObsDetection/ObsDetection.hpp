//
// Created by 최영수 on 2023/08/01.
//

#ifndef AMR_OBSDETECTION_HPP
#define AMR_OBSDETECTION_HPP

#include "Variables/Variable.hpp"
#include "Variables/mapinfo.hpp"

class ObsDetection {
private:
    struct obs_info{
        std::stack<coordinate> pos;
        int velocity;
        coordinate dir;
        std::stack<int> step;
    };
    struct Robot_status{
        int grad;
        int dy;
        int dx;
        coordinate next_pos;
        coordinate present_pos;
        int SensorRange;
    };
    Robot_status rs;
    int num_obs;

    obs_info labeled_obs[4];
    int labeling = 0;
    std::stack<int> detected_obs_num;
    bool isObstacle(int i, int j,int map[][100]);
    void updateGradient();
    bool isObstacleInSlope(int i, int j);
    void New_labeling(coordinate &obs_loc, int &step);
    void SaveObsTraj(coordinate new_obs, int &step);
    coordinate GetObsNextPos(int &i, int &iter);

public:
    void SetSensorRange(int SensorRange);
    void loadRobotStatus(coordinate pre, coordinate nex);
    int isObstacleDetected(int map[][100],coordinate &mapsize,int &step);
    int GetDetectedObsNum();
    void SetNumObstacle(int num_obs);
    int GetLabelData();
    void CollisionDetection(std::stack<coordinate> AMR_Traj);

private:
};

#endif //AMR_OBSDETECTION_HPP
