//
// Created by chansik on 23. 7. 27.
//
#include "astar/Astar.hpp"

Astar_planning::cell_data Astar_planning::Calculate_astar(int x, int y, int f, int x_p, int y_p) {
    cell_data result;
    int end_p_loc_x = end_point.first;
    int end_p_loc_y = end_point.second;
    result.h = sqrt((x - end_p_loc_x) * (x - end_p_loc_x) + (y - end_p_loc_y) * (y - end_p_loc_y));
    int a = abs(x_p - x);
    int b = abs(y_p - y);
    result.f = (a + b == 2) ? f + 1.4 : f + 1;
    result.g = result.h + result.f;
    result.parent_cell.first = x_p;
    result.parent_cell.second = y_p;
    return result;
}

std::stack<coordinate> Astar_planning::Astar(coordinate &start_point, coordinate &end_point, coordinate &mapsize, int map[][100]) {
    this->row = mapsize.first;
    this->column = mapsize.second;
    this->start_point = start_point;
    this->end_point = end_point;

    bool founddest = false;
    int x = this->start_point.first;
    int y = this->start_point.second;

    if (MapFunction::isOutofRange(x, y, mapsize) || MapFunction::isBlocked(x, y, map) ||
        MapFunction::isOutofRange(this->end_point.first, this->end_point.second, mapsize) ||
        MapFunction::isBlocked(this->end_point.first, this->end_point.second, map)) {
        std::cout << "start or end point error";
        //    return;
    }

    std::set<loc_data> openList;
    openList.insert(std::make_pair(0.0, std::make_pair(x, y)));

    bool closedList[row][column];
    std::memset(closedList, false, sizeof(closedList));

    while (!openList.empty()) {

        loc_data current_locate = *openList.begin();
        openList.erase(openList.begin());

        x = current_locate.second.first;
        y = current_locate.second.second;

        closedList[x][y] = true;
        if (MapFunction::isEndPoint(x, y, end_point)) {
            std::cout << "calculation finish \n";
            founddest = true;
            int a, b;
            a = cell[x][y].parent_cell.first;
            b = cell[x][y].parent_cell.second;
            while (a != this->start_point.first || b != this->start_point.second) {
                traj.push(std::make_pair(a, b));
                int a1 = cell[a][b].parent_cell.first;
                int b1 = cell[a][b].parent_cell.second;
                a = a1;
                b = b1;
            }
            traj.push(this->start_point);

            return traj;
        }
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                int a = i - x;
                int b = j - y;
                if (((x == 0 || y == 0) || (a != i && b != j)) && !MapFunction::isOutofRange(i, j, mapsize) &&
                    !MapFunction::isBlocked(i, j, map)) {

                    if (closedList[i][j]) continue;
                    cell_data a = Calculate_astar(i, j, cell[x][y].f, x, y);
                    if (cell[i][j].f == 0) { // first search
                        cell[i][j] = a;
                        openList.insert(std::make_pair(cell[i][j].g, std::make_pair(i, j)));
                    } else { // already include in openList
                        if (cell[i][j].g > a.g) cell[i][j] = a;
                        openList.insert(std::make_pair(cell[i][j].g, std::make_pair(i, j)));
                    }
                }
            }
        }
    }
    if (founddest == false) {
        std::cout << "destination not found.";
        //return;
    }
}
