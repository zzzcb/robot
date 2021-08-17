# 编译项目
cd catkin_ws 

catkin_make

# 控制真实UR5 
roslaunch ur_modern_driver ur5_bringup.launch robot_ip:=192.168.0.248 #启动ur_modern_driver，连接到真机ip【真机要和pc在同一局域网下】

roslaunch ur5_moveit_config ur5_moveit_planning_execution.launch      #moveit 路径规划,其实上一命令后就可以直接控制机械臂了，但可以利用moveit来规划路径

roslaunch ur5_moveit_config moveit_rviz.launch config:=true           #rviz可视化展示

# ur driver 相关
ur driver 有三种(要看自己UR机械臂的软件版本):

ur_driver(Polyscope versions < 1.8.x)  [已过期]

ur_modern_driver(1.8.x <= Polyscope versions < 3.7.x) [已过期]

ur_robot_driver(3.7.x  <= Polyscope versions)  [在维护]


# 机器人IO相关

https://answers.ros.org/question/368257/universal-robot-digital-io/

https://docs.ros.org/en/melodic/api/ur_msgs/html/srv/SetIO.html



