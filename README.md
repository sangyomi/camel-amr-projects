# 명령어
ros2 launch amr-gazebo-pkg maze_world.launch.py
// 환경 세팅

ros2 launch amr-obstacle-pkg dynamic_obstacle.launch.py
// 장애물 생성

ros2 run amr-main-pkg simulmain
// 메인 노드 


# 변수 수정 사항
start_point = ASTAR.traj.top();
end_point = ASTAR.Destx[ASTAR.count], ASTAR.Desty[ASTAR.count] ;
mapsize = ASTAR.ROW, ASTAR.COL;
map = zmap; 주의사항: int->char ( -1 -> * )
num_obs = 2;
sensor_range = 10;
present_pos = xAstar, yAstar;
next_pos = ASTAR.tra항j.top();
step = step;

# 장애물 인식시 넘겨줄 것들
OBS = std::vector<std::pair< int, std::pair<int,int>> 사이클마다 한번 씩
timer (실수단위의 시간 변수)
