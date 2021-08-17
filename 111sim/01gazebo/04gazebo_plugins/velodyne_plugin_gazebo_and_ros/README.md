# 这里与ros结合在一起，我们可以通过ros 发布topic消息，然后改变gazebo中velodyne_hdl-32 的速度
# 此时可以使用launch 来启动gazebo，launch文件配置参考: https://github.com/ros-simulation/gazebo_ros_pkgs/tree/melodic-devel/gazebo_ros/launch

# 开启gazebo
gazebo worlds/velodyne.world
roscore
rostopic pub /vel_cmd std_msgs/Float32 "data: 2.0"
## 如果配置了roslaunch 可以使用roslaunch


