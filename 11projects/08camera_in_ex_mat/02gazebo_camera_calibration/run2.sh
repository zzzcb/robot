#! /bin/bash

# launch a world with ur3 and kinect in gazebo 
x-terminal-emulator -e roslaunch camera_ex_cali_eyeonhand_pkg gazebo.launch & 
sleep 7 &&

# ros control
x-terminal-emulator -e roslaunch robot_control robot_control.launch 

# move_group 
x-terminal-emulator -e roslaunch eyeonhand_moveit_config move_group.launch

# moveit.rviz 手动选点
x-terminal-emulator -e roslaunch eyeonhand_moveit_config moveit_rviz.launch

