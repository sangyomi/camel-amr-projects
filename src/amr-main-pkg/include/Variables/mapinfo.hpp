//
// Created by ys on 23. 8. 11.
//

#ifndef AMR_MAPINFO_HPP
#define AMR_MAPINFO_HPP

namespace MapFunction{
    inline bool isOutofRange(int x, int y, coordinate &mapsize){
        return !(x >= 0 && x < mapsize.first && y >= 0 && y < mapsize.second);
    }
    inline bool isBlocked(int x, int y, int map[][100]) {
        return map[x][y] == 1;
    }
    inline bool isEndPoint(int x, int y, coordinate end_point) {
        return x == end_point.first && y == end_point.second;
    }
}

#endif //AMR_MAPINFO_HPP
