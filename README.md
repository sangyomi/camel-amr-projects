----
# Initial settings

### edit mesh filename


camel-amr-projects-V1/src/amr-gazebo-pkg/urdf/diffbot_amr.urdf 


    131: <mesh filename="/home/<Your Path>/camel-amr-projects/src/amr-gazebo-pkg/meshes/base_link.STL"/>


camel-amr-projects-V1/src/amr-gazebo-pkg/urdf/diffbot_amr_obstacle.urdf


    131: <mesh filename="/home/<Your Path>/camel-amr-projects/src/amr-gazebo-pkg/meshes/base_link.STL"/>

---
### build

    cd camel-amr-projects

    source /opt/ros/foxy/setup.bash

    colcon build --symlink-install


----
# Commend
Environment setting


    ros2 launch amr-gazebo-pkg maze_world.launch.py

Dynamic obstacle spawn and operate


    ros2 launch amr-obstacle-pkg dynamic_obstacle.launch.py

Main node


    ros2 run amr-main-pkg simulmain

----
# Print Map

if you want to check PathPlanning Map, edit simulmain.cpp 54 line


if you want to check Dynamic Obstacle Map, edit simulmain.cpp 54 line

----
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

----
# Dynamic Obstacle
    
    OBS = std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> 사이클마다 한번 씩
    
    timer  = double timer_cycle;
----
