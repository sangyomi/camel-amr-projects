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
    double quadratic_model(double x, double a, double b, double c);
    Eigen::VectorXd curve_fitting(const std::vector<double>& x_data, const std::vector<double>& y_data);
    void CurveFitting();
    void LinearRegression();
    void Prediction();
    void Prediction2();
public:
    bool CollisionDetectionCheck;
    std::pair<int,int> DynamicDestination;
    ObsDetection();
    void ClassifyObsData();
    void ObsPrediction();
    void ObsPredictionCurve();
    void Pred_Print();
    ~ObsDetection();
};

#endif //AMR_OBSDETECTION_HPP