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

using Pair = std::pair<int, int>;
using pPair = std::pair<double, Pair>;

struct Cell {
    int parent_x, parent_y;
    double f, g, h;
};

class Astar_planning {

public:
    int Destx[4];
    int Desty[4];
    double INF;
    char zmap[101][101];
    std::vector<std::vector<int>> Mapmatrix;
    int ROW;
    int COL;
    int count;
    int grid;
    std::stack<coordinate> traj;

    Astar_planning();
    bool isDestination(int row, int col, Pair dst);
    bool isInRange(int row, int col);
    bool isUnBlocked(std::vector<std::vector<int>>& map, int row, int col);
    double GethValue(int row, int col, Pair dst);
    void tracePath(Cell cellDetails[101][101], Pair dst);
    bool aStarSearch(std::vector<std::vector<int>>& map, Pair src, Pair dst);
    void PrintMap();
    void startAstar(int Startx, int Starty);
    ~Astar_planning();
};

#endif //SILJUN_ASTAR_HPP
