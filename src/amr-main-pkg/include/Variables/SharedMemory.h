//
// Created by dongju on 23. 9. 6.
//

#ifndef CAMEL_AMR_PROJECTS_SHAREDMEMORY_H
#define CAMEL_AMR_PROJECTS_SHAREDMEMORY_H
#include <Variables/Variable.hpp>

typedef struct _SHM_
{
    double heading;
    double xpos;
    double ypos;
    double duration;
    double AMRVelocity;
    double Dynamicobstacle_x;
    double Dynamicobstacle_y;

} SHM, *pSHM;

typedef struct _DSHM_
{
    std::vector<std::vector<double>> CostMap;
    std::vector<std::vector<int>> PresentMatrix;
    std::vector<Point> Clustered_point;
    std::vector<OBSINFO> obsLog;
    std::vector<COEFF> coeff_data;
    std::vector<COEFF2ND> coeff_sec_data;
    std::vector<std::pair<std::pair<int,int>, std::pair<double,double>>> LabelingArray;
} DSHM, *pDSHM;


#endif //CAMEL_AMR_PROJECTS_SHAREDMEMORY_H