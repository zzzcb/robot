# 机械臂从货架取下货物放到指定位置

 stage_description包为 放置机械臂的平台

 ur3_description包为 ur机械臂

 eg2_description包为 eg2 大寰夹爪


 robot_description包为 组装 上面三个urdf 的包

 robot_control包为 ros_control 相关的包

 robot_moveit_config包为 对robot进行moveit运动规划的包

 common_pkg包为 一些其他功能(在gazebo 加载货架,物料,传送带;在rviz中加载货架,物料,传送带)


# Moveit 结合gazebo时容易出错,有以下错误:
1 GOAL_TOLERANCE_VIOLATED    

    解决方法--> gazebo controllers.yaml中  添加  stopped_velocity_tolerance: 0  

    参考解决方案: https://answers.ros.org/question/312123/goal_tolerance_violated-gazebomoveit/

2 Controller arm_group_controller failed with error INVALID_GOAL: Trajectory message contains waypoints that are not strictly increasing in time.  

    解决方法--> 笛卡尔路径规划,去掉初始点 

    参考解决方案: https://answers.ros.org/question/253004/moveit-problem-error-trajectory-message-contains-waypoints-that-are-not-strictly-increasing-in-time/


