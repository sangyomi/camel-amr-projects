//
// Created by chansik on 23. 7. 27.
//

#include "Visualize/Map_In_Out.hpp"


void Map_In_Out::Map_Input(coordinate &start, coordinate &end,coordinate& mapsize, int map[][100]){

    int row = 100;
    int col = 100;
//    start = std::make_pair(0, 2);
//    end = std::make_pair(97, 99); //information from sensing process
    /* map size should be decided by sensing process */

    this->start = start;
    this->end = end;

    r = row;
    c = col;

    mapsize = std::pair<int, int>(r, c);
    return;
}

//void Map_In_Out::printMap(int map[][100]) {
//    map[start.first][start.second] = 2;
//    map[end.first][end.second] = 3;
//
//    for (int i = r -1; i >= 0; i--) {
//        for (int j = 0; j < c; j++) {
//            std::cout << map[i][j] << " ";
//        }
//        std::cout << "\n";
//    }
//    std::cout << std::endl;
//    return;
//}

void Map_In_Out::printMap(int map[][100],std::stack<coordinate> trajectory) {
    while(!trajectory.empty()) {
        if(map[trajectory.top().first][trajectory.top().second] == 5) {
            trajectory.pop();
            continue;
        }
        map[trajectory.top().first][trajectory.top().second] = -1;
        trajectory.pop();
    }
    map[start.first][start.second] = 2;
    map[end.first][end.second] = 3;
//
//    for (int i = r -1; i >= 0; i--) {
//        for (int j = 0; j < c; j++) {
//            if (map[i][j] == -1) {
//                std::cout << "*" << " ";
////                map[i][j] = 0;
//            }
//            else if(map[i][j] == 6) //obstacle's latest position
//                std::cout << "♣" << " ";
//            else std::cout << map[i][j] << " ";
//        }
//        std::cout << "\n";
//    }

    std::cout << std::endl;
    return;
}

/*
void DataOutPut(std::stack<coordinate>& trajectory) {
    std::stack<coordinate> tracked_path = trajectory;

    std::ofstream outfile("/home/ys/git/SilJun/planning/path.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error opening file for output.\n";
        return;
    }

    while (!tracked_path.empty()) {
        outfile << tracked_path.top().first << " " << tracked_path.top().second << "\n";
        map[tracked_path.top().first][tracked_path.top().second] = -1;
        tracked_path.pop();
    }

    outfile << end_point.first << " " << end_point.second << "\n";
//  printMap();  if necessary enable this line

}*/