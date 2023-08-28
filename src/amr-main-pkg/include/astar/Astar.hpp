//
// Created by chansik on 23. 7. 27.
//

#ifndef SILJUN_ASTAR_HPP
#define SILJUN_ASTAR_HPP

#include <utility>
#include <stack>
#include <set>
#include <vector>
#include <cmath>
#include <cstring>
#include <fstream>
#include "Variables/Variable.hpp"
#include "Variables/mapinfo.hpp"

class Astar_planning {

private:
    int row;
    int column;
    coordinate start_point;
    coordinate end_point;

    std::stack<coordinate> traj;

    struct cell_data {
        float f, g, h;
        coordinate parent_cell;
    };
    cell_data cell[100][100];
public:
    ///  global functions for  path planning  ///
    cell_data Calculate_astar(int x, int y, int f, int x_p, int y_p);

    std::stack<coordinate> Astar(coordinate &start_point, coordinate &end_point, coordinate &mapsize, int map[][100]);

};

#endif //SILJUN_ASTAR_HPP
