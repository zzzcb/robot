#! /bin/bash
# load launch gazebo
x-terminal-emulator -e roslaunch camera_in_cali_pkg gazebo.launch & # launch a empty world in gazebo 
sleep 3 &&

x-terminal-emulator -e roslaunch camera_in_cali_pkg spawn_kinect_chessboard.launch & # spawn a kinect and a chessboard to gazebo world

