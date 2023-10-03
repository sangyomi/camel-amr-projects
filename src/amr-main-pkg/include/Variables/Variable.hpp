//
// Created by ys on 23. 7. 31.
//

#ifndef AMR_VARIABLE_HPP
#define AMR_VARIABLE_HPP

#define PI 3.14159265

#include<iostream>
#include<stack>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>

typedef std::pair<int, int> coordinate;
typedef std::pair<double, coordinate> loc_data; // detailed data;
typedef std::pair<double, coordinate> TimeLoc; // Time[ms], coordinate
typedef struct _COEFFICIENTDATA_{
    // x = c1 + a*t
    // y = c2 + b*t
    double a;
    double c1;
    double b;
    double c2;
    double xloss;
    double yloss;
} COEFF, *pCOEFF; // for LinearRegression

typedef struct _OBSINFO_
{
    int label; // 장애물 이름
    std::vector<TimeLoc> obsLocationLog; // 장애물 위치 기록
    std::vector<TimeLoc> obsPredLoc; // 장애물 미래 위치
    int loss; // 회귀분석 loss값
    COEFF coeff_data; // 회귀분석 계수
    bool labelcheck;
    bool regDataCheck;
} OBSINFO, *pOBSINFO;

#endif //AMR_VARIABLE_HPP