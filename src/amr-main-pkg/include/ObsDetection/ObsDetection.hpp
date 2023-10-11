//
// Created by 최영수 on 2023/08/01.
//

#ifndef AMR_OBSDETECTION_HPP
#define AMR_OBSDETECTION_HPP

#include "Variables/Variable.hpp"
#include "Variables/mapinfo.hpp"
#include "Variables/SharedMemory.h"
#include <eigen3/Eigen/Dense>


class ObsDetection {

private:
    std::vector<OBSINFO> ObsPredPoint;

public:
    bool CollisionDetectionCheck;
    std::pair<int,int> DynamicDestination;
    ObsDetection();
    void ClassifyObsData();
    void LinearRegression();
    void Prediction();
    void Pred_Print();
    int GetNum_ObsPredPoint();
    std::vector<coordinate>  GetObsPredPoint(int &num);
    ~ObsDetection();
};

#endif //AMR_OBSDETECTION_HPP