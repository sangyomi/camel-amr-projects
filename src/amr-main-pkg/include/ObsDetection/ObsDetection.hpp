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

class ObsDetection {
    typedef std::pair<double, coordinate> TimeLoc;

private:
    struct obs_info{
        std::stack<TimeLoc> timepos;
        int label;
        bool labelcheck;
        int loss;
    };

    std::vector<obs_info> ObsLog;
    std::vector<obs_info> ObsPredPoint;
public:
    void Print();
    void SaveObsInfo(std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> &LidarData, int time);
    void Prediction();
    void Pred_Print();

};

#endif //AMR_OBSDETECTION_HPP