//
// Created by chansik on 23. 7. 27.
//

#ifndef SILJUN_MAP_IN_OUT_HPP
#define SILJUN_MAP_IN_OUT_HPP

#include "Variables/Variable.hpp"

class Map_In_Out{
private:
    coordinate start;
    coordinate end;

    int r;
    int c;

public:
    void Map_Input(coordinate &start, coordinate &end, coordinate &mapsize, int map[][100]);
    void printMap(int map[][100]);
    void printMap(int map[][100], std::stack<coordinate> trajectory);

    void DataOutPut(std::stack<coordinate>& trajectory);

};

#endif //SILJUN_MAP_IN_OUT_HPP
