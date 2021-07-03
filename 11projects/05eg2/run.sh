#! /bin/bash
# load description and launch gazebo
x-terminal-emulator -e roslaunch eg2_description gazebo.launch &
sleep 3 &&
# load and start controller
x-terminal-emulator -e roslaunch eg2_control eg2.launch &
sleep 3 &&
# load move group
x-terminal-emulator -e roslaunch eg2_moveit_config move_group.launch &

sleep 5 &&
# load rviz,手点就可以进行运动规划
x-terminal-emulator -e roslaunch eg2_moveit_config moveit_rviz.launch


