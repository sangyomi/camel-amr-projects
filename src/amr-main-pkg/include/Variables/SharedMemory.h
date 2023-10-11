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
} SHM, *pSHM;

typedef struct _DSHM_
{
    std::vector<std::vector<double>> CostMap;
    std::vector<OBSINFO> obsLog;
    std::vector<COEFF> coeff_data;
    std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> LabelingArray;
} DSHM, *pDSHM;


#endif //CAMEL_AMR_PROJECTS_SHAREDMEMORY_H