//
// Created by 최영수 on 2023/08/01.
//

#include "DynamicObstacle/DynamicObstacle.hpp"

int obs_numcount = 0;

void DynamicObstacle::Initialize() {
    pos = GenerateRandomCoordinate();
    dir = GenerateRandomDirection();
//    velocity = static_cast<double>(rand() % 2 + 1);
    velocity = 1;
}
void DynamicObstacle::ApplyToMap(int map[][100]) {
    map[pos.first][pos.second] = 4;
//    std::cout << "obs init pos : " << "(" << pos.first << "," << pos.second << ")" << std::endl;
//    std::cout << "velocity : " << velocity << std::endl;
//    std::cout << "direction : " << dir.first << dir.second << std::endl;
//    std::cout << "-------------------------" << std::endl;
}
coordinate DynamicObstacle::GenerateRandomCoordinate() {
    obs_numcount++;
    if(obs_numcount ==4)             //random moving obstacle
        return {rand()%30+50,rand()%30+15};
    else if(obs_numcount ==5)
        return {rand()%30+20,rand()%30+55};
    else                             //diagonal moving obsatcle
        return {rand() % 40 + 30, rand() % 40 + 30};
}
coordinate DynamicObstacle::GenerateRandomDirection() {

    if(obs_numcount >= 4)            //random moving obstacle
        return {GenerateRandomDirectionComponent(), GenerateRandomDirectionComponent()};
    else                             //diagonal moving obsatcle
        return {1, -1};
}
int DynamicObstacle::GenerateRandomDirectionComponent() {
    return rand()%2 - 1;
}

void DynamicObstacle::UpdateObstacle(int map[][100], coordinate &mapsize){
   // 30~70 좌표 사이에 obstacle 생성 후 매번 업뎃.

//    map[pos.first][pos.second] = 0; current coordinate elimination in map
    obs_numcount++;
    map[pos.first][pos.second] = 4;  // 4: old obstacle path

    if(obs_numcount%5==4 || obs_numcount%5==0){ //random moving obsatcle
        if(MapFunction::isOutofRange(pos.first + dir.first*velocity, pos.second+ dir.second*velocity,mapsize)){
            dir.first  = -dir.first;
            dir.second = -dir.second;
            pos = std::make_pair(pos.first + dir.first*velocity,pos.second+ dir.second*velocity);
        }
        else{
            dir.first = rand()%2-1;
            dir.second = rand()%2-1;
            pos = std::make_pair(pos.first + dir.first*velocity,pos.second+ dir.second*velocity);
        }
    }
    else if ( (obs_numcount%5>0) && (obs_numcount%5<4) && ((pos.first <=30 || pos.second <=30) || (pos.first >=70 || pos.second >=70))){ //bidirectional moving : revert direction
        dir.first = -dir.first;
        dir.second = -dir.second;
        pos = std::make_pair(pos.first + dir.first*velocity,pos.second+ dir.second*velocity);
    }
    else //bidirectional moving
        pos = std::make_pair(pos.first + dir.first*velocity,pos.second+ dir.second*velocity);


    map[pos.first][pos.second] = 6;          //update next position in the map, 6 : updated obstacle path, clover pattern in terminal output map

//    std::cout << "-----------<obstacle pos, vel, dir>-----------" << std::endl;
//    std::cout << "obs next position : " << "(" << pos.first << "," << pos.second << ")" << std::endl;
//    std::cout << "check_velocity : " << velocity << std::endl;
//    std::cout <<"obs direction : " << dir.first << "," << dir.second << std::endl;
    move_iter++;
//    std::cout << "obs moving iteration(test) : " << move_iter << std::endl;
//    std::cout <<"obs_numcount : " <<obs_numcount << std::endl;
}

//}