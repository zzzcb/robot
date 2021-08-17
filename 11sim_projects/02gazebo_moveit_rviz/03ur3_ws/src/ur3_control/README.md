# 该 pkg 是 ros_control 的包

#两个 controller 
#1 arm_group_controller 它的类型是position_controllers/JointTrajectoryController,可以理解为Moveit对应topic的ActionServer
#2 joint_state_controller,它不是控制，而是发送joint_state出来
