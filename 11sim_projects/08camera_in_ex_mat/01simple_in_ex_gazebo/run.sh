#! /bin/bash
# load launch gazebo
x-terminal-emulator -e roslaunch common_pkg gazebo_table.launch & # launch gazebo with a table 
sleep 3 &&

x-terminal-emulator -e roslaunch common_pkg spawn_kinect.launch & # spawn kinect to gazebo world

sleep 3 &&
x-terminal-emulator -e rosrun common_pkg calc_table_pos 

