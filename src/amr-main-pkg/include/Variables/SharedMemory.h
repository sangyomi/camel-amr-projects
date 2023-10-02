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
    std::vector<coefficientData> coeff_data;

} SHM, *pSHM;


#endif //CAMEL_AMR_PROJECTS_SHAREDMEMORY_H