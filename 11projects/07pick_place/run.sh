#! /bin/bash
# load robot description and launch gazebo
x-terminal-emulator -e roslaunch robot_description gazebo.launch &
sleep 3 &&

# load material
x-terminal-emulator -e roslaunch common_pkg load_material.launch target_material_idx:=-1 & # 随机位置生成
#x-terminal-emulator -e roslaunch common_pkg load_material.launch  &
sleep 5 &&

# spawn material
x-terminal-emulator -e roslaunch common_pkg spawn_material.launch &

## load and start controller
#x-terminal-emulator -e roslaunch robot_control robot_control.launch &
#sleep 3 &&
## load move group
#x-terminal-emulator -e roslaunch robot_moveit_config move_group.launch &
#
#sleep 5 &&
## load rviz,手点就可以进行运动规划
#x-terminal-emulator -e roslaunch robot_moveit_config moveit_rviz.launch
