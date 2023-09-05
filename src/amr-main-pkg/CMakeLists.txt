cmake_minimum_required(VERSION 3.5)
project(amr-main-pkg)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -fPIC")
endif()

if(NOT DEFINED BUILD_VERSION)
  set(BUILD_VERSION "not set")
endif()

add_definitions(-DBUILD_VERSION="${BUILD_VERSION}")

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(amr_msg_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(rmw_implementation REQUIRED)
find_package(std_msgs REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Widgets REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
        include
        ${std_msgs_INCLUDE_DIRS}
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Quick_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
)

add_library(astar_lib
        src/astar/Astar.cpp
)

add_library(visualize_lib
        src/Visualize/Map_In_Out.cpp
)

add_library(dynamicObstacle_lib
        src/DynamicObstacle/DynamicObstacle.cpp
)

add_library(obsDetection_lib
        src/ObsDetection/ObsDetection.cpp
)

add_library(clusteringDynamicObs_lib
        src/ClusteringDynamicObs/ClusteringDynamicObs.cpp
)

#add_library(main_gui_lib
#        src/ros2_ui/main_GUI.cpp
#)

target_include_directories(astar_lib PUBLIC include)
target_include_directories(visualize_lib PUBLIC include)
target_include_directories(dynamicObstacle_lib PUBLIC include)
target_include_directories(obsDetection_lib PUBLIC include)
target_include_directories(clusteringDynamicObs_lib PUBLIC include)

ament_target_dependencies(astar_lib rclcpp)
ament_target_dependencies(visualize_lib rclcpp)
ament_target_dependencies(dynamicObstacle_lib rclcpp)
ament_target_dependencies(obsDetection_lib rclcpp)
ament_target_dependencies(clusteringDynamicObs_lib rclcpp)


install(
        DIRECTORY include/
        DESTINATION include
)

install(TARGETS
        astar_lib
        visualize_lib
        dynamicObstacle_lib
        obsDetection_lib
        clusteringDynamicObs_lib
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

add_executable(simulmain
        src/simulmain/simul_main.cpp
        src/simulmain/mainwindow.cpp
        src/simulmain/qcustomplot.cpp
)

ament_target_dependencies(simulmain
        amr_msg_interfaces
        rclcpp
        sensor_msgs
        geometry_msgs
        nav_msgs
        std_msgs
        rmw_implementation
)

target_link_libraries(simulmain
        astar_lib
        visualize_lib
        dynamicObstacle_lib
        obsDetection_lib
        clusteringDynamicObs_lib
        Qt5::Core
        Qt5::Quick
        Qt5::Widgets
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
  find_package(ament_cmake_gtest REQUIRED)

endif()

install(TARGETS
        simulmain
        DESTINATION lib/${PROJECT_NAME}
)


install(DIRECTORY launch param
        DESTINATION share/${PROJECT_NAME}
)

# install(TARGETS ros2_ui DESTINATION bin)

ament_package()
