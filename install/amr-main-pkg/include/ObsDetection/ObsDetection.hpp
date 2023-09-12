//
// Created by 최영수 on 2023/08/01.
//

#ifndef AMR_OBSDETECTION_HPP
#define AMR_OBSDETECTION_HPP

#include "Variables/Variable.hpp"
#include "Variables/mapinfo.hpp"
#include <cmath>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class ObsDetection {

private:
    struct obs_info{
        std::vector<TimeLoc> timepos;
        int label;
        bool labelcheck;
        int loss;

    };
    std::vector<obs_info> ObsLog;
    std::vector<obs_info> ObsPredPoint;
public:
    bool CollisionDetectionCheck;
    std::pair<int,int> DynamicDestination;
    ObsDetection();
    void SaveObsInfo(std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> &LidarData, double time);
    void LinearRegression();
    void Prediction(int step, int stepsize);
    void Pred_Print();
    void Print();
    int GetNum_ObsPredPoint();
    std::vector<coordinate>  GetObsPredPoint(int &num);
    std::vector<coefficientData> coeff_data;
    ~ObsDetection();
};

#endif //AMR_OBSDETECTION_HPP