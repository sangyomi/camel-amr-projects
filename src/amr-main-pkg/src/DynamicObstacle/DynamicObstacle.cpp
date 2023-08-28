//
// Created by 최영수 on 2023/08/01.
//

#include "DynamicObstacle/DynamicObstacle.hpp"

int obs_numcount = 0;



void DynamicObstacle::Initialize() {
    std::cout << "Select Obstacle type- a.Straight moving, b. weak inclined moving : ";
    std::cin >> type; /// 버퍼 엔터키 씹히면 지워주기
    std::cin.ignore();
    SetObsCoordinate();
    SetObsdirection();
    velocity = 1;
    //    velocity = static_cast<double>(rand() % 2 + 1);

}
void DynamicObstacle::ApplyToMap(int map[][100]) {
    map[pos.first][pos.second] = 4;
//    std::cout << "obs init pos : " << "(" << pos.first << "," << pos.second << ")" << std::endl;
//    std::cout << "velocity : " << velocity << std::endl;
//    std::cout << "user_direction : " << dir.first << dir.second << std::endl;
//    std::cout << "-------------------------" << std::endl;
}
void DynamicObstacle::SetObsCoordinate() {

    std::cout << "Set obstacle position : ";
    std::cin >> pos.first >> pos.second;
    std::cin.ignore();
//    obs_numcount++;
//    if(obs_numcount ==4)             //random moving obstacle
//        return {rand()%30+50,rand()%30+15};
//    else if(obs_numcount ==5)
//        return {rand()%30+20,rand()%30+55};
//    else                             //diagonal moving obsatcle
//        return {rand() % 40 + 30, rand() % 40 + 30};
}
void DynamicObstacle::SetObsdirection() {
    if(type == 'a'){
        std::cout <<"Set obstacle user_direction. 6 = right, 4 = left : ";
        std::cin >> user_direction;
        std::cin.ignore();
        switch (user_direction){
            case 6:
                dir.first = 0;
                dir.second = 1;
                break;
            case 4:
                dir.first = 0;
                dir.second = -1;
                break;
        }
    }
    else if(type == 'b'){
        std::cout << "Set obstacle user_direction. 9 =  up right, 3 = down right, 7 = up left, 1 = down left : ";
        std::cin >> user_direction;
        std::cin.ignore();
        switch(user_direction){
            case 9:
                dir.first = 1;
                dir.second = 1;
                break;
            case 7:
                dir.first = 1;
                dir.second = -1;
                break;
            case 3:
                dir.first = -1;
                dir.second = 1;
                break;
            case 1:
                dir.first = -1;
                dir.second = -1;
                break;
        }

    }
//    if(obs_numcount >= 4)            //random moving obstacle
//        return {GenerateRandomDirectionComponent(), GenerateRandomDirectionComponent()};
//    else                             //diagonal moving obsatcle
//        return {1, -1};
}

int DynamicObstacle::GenerateRandomDirectionComponent() {
    return rand()%2 - 1;
}

void DynamicObstacle::UpdateObstacle(int map[][100], coordinate &mapsize){

//    map[pos.first][pos.second] = 0; current coordinate elimination in map

//    obs_numcount++;
    map[pos.first][pos.second] = 4;  // 4: old obstacle path

    if(type == 'a'){ /// straight line moving
        if(MapFunction::isOutofRange(pos.first+dir.first*velocity,pos.second+dir.second*velocity,mapsize)){
            map[pos.first][pos.second] = 6;
            return;
        }
        pos = std::make_pair(pos.first+dir.first*velocity,pos.second+dir.second*velocity); /// update obstacle position
    }
    else if(type == 'b'){
        pos = Inclined_moving(mapsize);
    }
    map[pos.first][pos.second] = 6;          //update next position in the map, 6 : updated obstacle path, clover pattern in terminal output map


//    if(obs_numcount%5==4 || obs_numcount%5==0){ //random moving obsatcle
//        if(MapFunction::isOutofRange(pos.first + dir.first*velocity, pos.second+ dir.second*velocity,mapsize)){
//            dir.first  = -dir.first;
//            dir.second = -dir.second;
//            pos = std::make_pair(pos.first + dir.first*velocity,pos.second+ dir.second*velocity);
//        }
//        else{
//            dir.first = rand()%2-1;
//            dir.second = rand()%2-1;
//            pos = std::make_pair(pos.first + dir.first*velocity,pos.second+ dir.second*velocity);
//        }
//    }
//    else if ( (obs_numcount%5>0) && (obs_numcount%5<4) && ((pos.first <=30 || pos.second <=30) || (pos.first >=70 || pos.second >=70))){ //bidirectional moving : revert user_direction
//        dir.first = -dir.first;
//        dir.second = -dir.second;
//        pos = std::make_pair(pos.first + dir.first*velocity,pos.second+ dir.second*velocity);
//    }
//    else //bidirectional moving
//        pos = std::make_pair(pos.first + dir.first*velocity,pos.second+ dir.second*velocity);



//    std::cout << "-----------<obstacle pos, vel, dir>-----------" << std::endl;
//    std::cout << "obs next position : " << "(" << pos.first << "," << pos.second << ")" << std::endl;
//    std::cout << "check_velocity : " << velocity << std::endl;
//    std::cout <<"obs user_direction : " << dir.first << "," << dir.second << std::endl;
//    move_iter++;
//    std::cout << "obs moving iteration(test) : " << move_iter << std::endl;
//    std::cout <<"obs_numcount : " <<obs_numcount << std::endl;
}

//}

coordinate DynamicObstacle::Inclined_moving(coordinate &mapsize) {

    if(MapFunction::isOutofRange(pos.first+dir.first*velocity,pos.second+dir.second*velocity,mapsize)){
        return pos; ///don't update obstacle if it will become out of range
    }

    if(user_direction == 9){ /// up right moving
        move_count++;
        if(move_count%2 == 1){
            dir.first = 1;
            dir.second = 1;
        }
        else{
            dir.first = 0;
            dir.second = 1;
        }
        return(std::make_pair(pos.first+dir.first*velocity,pos.second+dir.second*velocity));
    }
    else if(user_direction == 7) {
        move_count++;
        if(move_count%3 == 1){
            dir.first = 1;
            dir.second = -1;
        }
        else{
            dir.first = 0;
            dir.second = -1;
        }
        return(std::make_pair(pos.first+dir.first*velocity,pos.second+dir.second*velocity));
    }
    else if(user_direction == 3){
        move_count++;
        if(move_count%3 == 1){
            dir.first = -1;
            dir.second = 1;
        }
        else{
            dir.first = 0;
            dir.second = 1;
        }
        return(std::make_pair(pos.first+dir.first*velocity,pos.second+dir.second*velocity));
    }
    else{
        move_count++;
        if(move_count%3 == 1){
            dir.first = -1;
            dir.second = -1;
        }
        else{
            dir.first = 0;
            dir.second = -1;
        }
        return(std::make_pair(pos.first+dir.first*velocity,pos.second+dir.second*velocity));
    }

}