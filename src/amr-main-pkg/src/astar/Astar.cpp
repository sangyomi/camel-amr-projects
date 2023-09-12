//
// Created by chansik on 23. 7. 27.
//
#include "astar/Astar.hpp"
#define MAX 101
#define GRID 100
#define GAZEBOGRID 20
#define PI 3.14159265

enum Initseting{
    grid=100,
    Startx=0,
    Starty=0,
};

Astar_planning::Astar_planning()
        : Mapmatrix(GRID, std::vector<int>(GRID, 0)), dx1{0, -1, 0, 1}, dy1{-1, 0, 1, 0},
          dx2{1, -1, -1, 1}, dy2{-1, -1, 1, 1}, Destx{90, 10, 90, 10}, Desty{10, 90, 10, 90},
          direction{0,-1*PI*0.25,-1*PI*0.5,-1*PI*0.75,PI,PI*0.75,PI*0.5,PI*0.25,0}
{
    CollisionDetectionCheck = false;
    grid = 100;
    INF = 1e9+7;
    ROW = grid;
    COL = grid;
    count = 0;
}


bool Astar_planning::isDestination(int row, int col, Pair dst) {
    if (row == dst.first && col == dst.second) return true;
    return false;
}

bool Astar_planning::isInRange(int row, int col) {
    return (row >= 0 && row < ROW && col >= 0 && col < COL);
}

bool Astar_planning::isUnBlocked(std::vector<std::vector<int>>& map, int row, int col) {
    return (map[row][col] == 0);
}

double Astar_planning::GethValue(int row, int col, Pair dst) {
    return (double)std::sqrt(std::pow(row - dst.first, 2) + std::pow(col - dst.second, 2));
}

void Astar_planning::tracePath(Cell cellDetails[MAX][MAX], Pair dst) {
    std::stack<Pair> s;
    int y = dst.first;
    int x = dst.second;

    s.push({ y, x });
    while (!(cellDetails[y][x].parent_x == x && cellDetails[y][x].parent_y == y)) {
        int tempy = cellDetails[y][x].parent_y;
        int tempx = cellDetails[y][x].parent_x;
        y = tempy;
        x = tempx;
        s.push({ y, x });
        traj.push({y,x});
    }


    while (!s.empty()) {
        zmap[s.top().first][s.top().second] = '*';
        s.pop();
    }
}

bool Astar_planning::aStarSearch(std::vector<std::vector<int>>& map, Pair src, Pair dst) {
    if (!isInRange(src.first, src.second) || !isInRange(dst.first, dst.second)) return false;
    if (!isUnBlocked(map, src.first, src.second) || !isUnBlocked(map, dst.first, dst.second)) return false;
    if (isDestination(src.first, src.second, dst)) return false;

    bool closedList[MAX][MAX];
    std::memset(closedList, false, sizeof(closedList));

    Cell cellDetails[MAX][MAX];

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            cellDetails[i][j].f = cellDetails[i][j].g = cellDetails[i][j].h = INF;
            cellDetails[i][j].parent_x = cellDetails[i][j].parent_y = -1;
        }
    }

    int sy = src.first;
    int sx = src.second;
    cellDetails[sy][sx].f = cellDetails[sy][sx].g = cellDetails[sy][sx].h = 0.0;
    cellDetails[sy][sx].parent_x = sx;
    cellDetails[sy][sx].parent_y = sy;

    std::set<pPair> openList;
    openList.insert({ 0.0, { sy, sx } });

    while (!openList.empty()) {
        pPair p = *openList.begin();
        openList.erase(openList.begin());

        int y = p.second.first;
        int x = p.second.second;
        closedList[y][x] = true;

        double ng, nf, nh;

        for (int i = 0; i < 4; ++i) {
            int ny = y + dy1[i];
            int nx = x + dx1[i];

            if (isInRange(ny, nx)) {
                if (isDestination(ny, nx, dst)) {
                    cellDetails[ny][nx].parent_y = y;
                    cellDetails[ny][nx].parent_x = x;
                    tracePath(cellDetails, dst);
                    return true;
                }

                else if (!closedList[ny][nx] && isUnBlocked(map, ny, nx)) {
                    ng = cellDetails[y][x].g + 1.0;
                    nh = GethValue(ny, nx, dst);
                    nf = ng + nh;

                    if (cellDetails[ny][nx].f == INF || cellDetails[ny][nx].f > nf) {
                        cellDetails[ny][nx].f = nf;
                        cellDetails[ny][nx].g = ng;
                        cellDetails[ny][nx].h = nh;
                        cellDetails[ny][nx].parent_x = x;
                        cellDetails[ny][nx].parent_y = y;
                        openList.insert({ nf, { ny, nx } });
                    }
                }
            }
        }

        for (int i = 0; i < 4; ++i) {
            int ny = y + dy2[i];
            int nx = x + dx2[i];

            if (isInRange(ny, nx)) {
                if (isDestination(ny, nx, dst)) {
                    cellDetails[ny][nx].parent_y = y;
                    cellDetails[ny][nx].parent_x = x;
                    tracePath(cellDetails, dst);
                    return true;
                }
                else if (!closedList[ny][nx] && isUnBlocked(map, ny, nx)) {
                    ng = cellDetails[y][x].g + 1.414;
                    nh = GethValue(ny, nx, dst);
                    nf = ng + nh;

                    if (cellDetails[ny][nx].f == INF || cellDetails[ny][nx].f > nf) {
                        cellDetails[ny][nx].f = nf;
                        cellDetails[ny][nx].g = ng;
                        cellDetails[ny][nx].h = nh;
                        cellDetails[ny][nx].parent_x = x;
                        cellDetails[ny][nx].parent_y = y;
                        openList.insert({ nf, { ny, nx } });
                    }
                }
            }
        }
    }

    return false;
}

void Astar_planning::PrintMap() {
    std::cout<< "\n";
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            std::cout << zmap[i][j];
//            std::cout << Mapmatrix[i][j];
        }
        std::cout << '\n';
    }
}

void Astar_planning::startAstar(std::vector<coordinate> Path)
{
    coordinate src, dst;
    while(!traj.empty())traj.pop();
    for(int i = Path.size()-1; i >=0; i--){
        src = {Path[i].first, Path[i].second};
        dst = {Path[i+1].first, Path[i+1].second};
        for (int k = 0; k < ROW; ++k) {
            for (int j = 0; j < COL; ++j) {
                zmap[k][j] = Mapmatrix[k][j] + '0';
            }
        }
        aStarSearch(Mapmatrix, src, dst);
    }
}

void Astar_planning::AmrFuturePath(std::stack<coordinate> amrtraj, double velocity){
    std::stack<coordinate> temp = amrtraj;
    int i=0, num=0;
    double gridDistance = (double)GAZEBOGRID/(double)GRID;

    for(int i=0; i<futuretraj.size(); i++){
        while(!futuretraj.empty()){
            futuretraj.erase(futuretraj.begin());
        }
    }
    if(velocity == 0){
        futuretraj.push_back(amrtraj.top());
        return;
    }

    futuretraj.push_back(temp.top());
    temp.pop();    /// 현재 AMR 좌표는 버리고 다음스텝부터 t+1,t+2,,,,

    int step = velocity/gridDistance; /// 몇 step 가야 1초가 걸리는지 ex)  0.4m/s * 1초 = 0.2m(20/100,그리드1칸 간격) * step, step = 0.4/0.2 = 2
    if(velocity<gridDistance && step ==0){     /// ex)  속도가 0.05ms * 1초 = 0.2m * x ==> 4초에 1칸 전진,,
// 나중에 처리
    }
    while(num<5 && !temp.empty() ){
        i++;
        if(i%step == 0){
            futuretraj.push_back(temp.top()); /// ex) 속도가 0.4m/s일 경우, step=2칸을 이동한 경우가 1초 이므로, 2칸 간격으로 뽑아냄
            num++;
        }
        if( (num!=5) && (temp.top().first == Destx[count] && temp.top().second == Desty[count])
            && !(futuretraj.back().first == Destx[count] && futuretraj.back().second == Desty[count]) ) {
            futuretraj.push_back(temp.top());
            break;
        }

        temp.pop();
    }

/// 프린트 테스트
    std::cout << "AMR 미래 경로(초 단위) : ";
    for(int j=0; j<futuretraj.size(); j++){
        std::cout << "(" << futuretraj[j].first << "," << futuretraj[j].second << ")" << "  ";
    }
    std::cout << std::endl;
//    std::cout << "AMR 전체 경로 : ";
//    while(!temp.empty()){
//        std::cout << "(" << temp.top().first << "," << temp.top().second << ")" << "  ";
//        temp.pop();
//    }
//    std::cout << std::endl;
}




Astar_planning::~Astar_planning()
{

}