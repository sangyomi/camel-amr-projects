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

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(amr_msg_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

include_directories(include)

add_library(AMR_library src/DynamicObstacle/DynamicObstacle.cpp src/ObsDetection/ObsDetection.cpp src/PathPlanning/Astar.cpp src/Visualize/Map_In_Out.cpp)

ament_export_targets(AMR_library HAS_LIBRARY_TARGET)

install(
        DIRECTORY include/DynamicObstacle include/ObsDetection include/PathPlanning include/Visualize include/Variables
        DESTINATION include
)

install(
        TARGETS AMR_library
        EXPORT AMR_library
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)


add_executable(simulmain src/simulmain/simul_main.cpp)
ament_target_dependencies(simulmain
        amr_msg_interfaces
        rclcpp
        sensor_msgs
        geometry_msgs
        nav_msgs
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

ament_package()
