//
// Created by 최영수 on 2023/08/01.
//

#ifndef AMR_DYNAMICOBSTACLE_HPP
#define AMR_DYNAMICOBSTACLE_HPP

#include "Variables/Variable.hpp"
#include "Variables/mapinfo.hpp"

class DynamicObstacle {
private:
    coordinate pos;
    coordinate dir;
    double velocity;

    char type; /// obstale type : straight, inclined
    int move_count = 0; /// variable just for inclined obstacle moving
    int user_direction; /// command for obstacle direction select

    int move_iter; //for obstacle moving test


public:
    void Initialize();
    void ApplyToMap(int map[][100]);
    void UpdateObstacle(int map[][100], coordinate &mapsize);

private:
    void SetObsCoordinate();
    void SetObsdirection();
    coordinate Inclined_moving(coordinate &mapsize);
    int GenerateRandomDirectionComponent();
};

#endif //AMR_DYNAMICOBSTACLE_HPP
