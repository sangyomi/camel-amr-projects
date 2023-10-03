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
} SHM, *pSHM;

typedef struct _DSHM_
{
    std::vector<OBSINFO> obsLog;
    std::vector<COEFF> coeff_data;
} DSHM, *pDSHM;


#endif //CAMEL_AMR_PROJECTS_SHAREDMEMORY_H