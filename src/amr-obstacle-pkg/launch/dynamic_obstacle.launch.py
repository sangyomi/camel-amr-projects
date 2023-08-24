import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='amr-obstacle-pkg',
            executable='spawn_dynamic_obstacle_node',
            name='spawn_dynamic_obstacle_node',
            output='screen'
        ),
        Node(
            package='amr-obstacle-pkg',
            executable='operate_dynamic_obstacle_node',
            name='operate_dynamic_obstacle_node',
            output='screen'
        ),
    ])