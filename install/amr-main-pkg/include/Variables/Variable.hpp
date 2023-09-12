//
// Created by ys on 23. 7. 31.
//

#ifndef AMR_VARIABLE_HPP
#define AMR_VARIABLE_HPP

#include<iostream>
#include<stack>
typedef std::pair<int, int> coordinate;
typedef std::pair<double, coordinate> loc_data; // detailed data;
typedef std::pair<double, coordinate> TimeLoc; // Time[ms], coordinate
typedef std::pair<std::pair<double, double>, std::pair<double, double>> coefficientData; // for LinearRegression

#endif //AMR_VARIABLE_HPP