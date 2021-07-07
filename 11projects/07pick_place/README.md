# 机械臂从货架取下货物放到指定位置

 stage_description包为 放置机械臂的平台

 ur3_description包为 ur机械臂

 eg2_description包为 eg2 大寰夹爪


 robot_description包为 组装 上面三个urdf 的包

 robot_control包为 ros_control 相关的包

 robot_moveit_config包为 对robot进行moveit运动规划的包

 common_pkg包为 一些其他功能(在gazebo 加载货架,物料,传送带;在rviz中加载货架,物料,传送带)

# 关于PID调试
Here are typical steps for setting PID gains empirically (aka by trial and error):

1. Increase your P gain until the actual value reaches the desired value in the desired amount of time (rise time). This will typically result in large oscillations that take a while to settle down... but that will be fixed later. For now, just focus on rise time. Make sure that your P is low enough that the system remains stable (aka the oscillations die off after a certain amount of time). If your actual value will not reach your desired value no matter how high you set your P gain, skip to step 3.

2. Increase your D gain to reduce the oscillations until you reach your desired settling time (aka the time it takes for the oscillations to fall below +/- 5% of the desired value). Be careful here, D gains are very sensitive and can cause very noisy responses, especially when you are working with a discrete system with relatively large time steps (like in simulation).

3. If your system has steady state error (aka no value of P gain can get the actual value to reach the desired value), start increasing your I gain until the steady state error disappears in a satisfactory amount of time.
4. Repeat steps 1-3 to continuously fine tune the PID controller.

The general idea here is to start with small gains, and run through these steps several times, changing the gains a little bit each time. Hope that helps!


# Moveit 结合gazebo时容易出错,有以下错误:
1 GOAL_TOLERANCE_VIOLATED    

    解决方法--> gazebo controllers.yaml中  添加  stopped_velocity_tolerance: 0  

    参考解决方案: https://answers.ros.org/question/312123/goal_tolerance_violated-gazebomoveit/

2 Controller arm_group_controller failed with error INVALID_GOAL: Trajectory message contains waypoints that are not strictly increasing in time.  

    解决方法--> 笛卡尔路径规划,去掉初始点 

    参考解决方案: https://answers.ros.org/question/253004/moveit-problem-error-trajectory-message-contains-waypoints-that-are-not-strictly-increasing-in-time/


