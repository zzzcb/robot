//
// Created by zcb on 6/19/21.
//
/*
 * 参考:
 * http://docs.ros.org/en/melodic/api/moveit_tutorials/html/doc/move_group_interface/move_group_interface_tutorial.html
 */
#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char **argv) {
    //初始化 节点
    std::string nodeName = "move_group_cpp_interface";
    ros::init(argc, argv, nodeName); // 此行代码不会与 master 联系

    // When the first ros::NodeHandle is created it will call ros::start(), and when the last
    // ros::NodeHandle is destroyed, it will call ros::shutdown().
    // If you want to manually manage the lifetime of the node you may call ros::start() yourself,
    // in which case you should call ros::shutdown() before your program exits.
    ros::NodeHandle node;            // 这行才会与master联系

    ros::AsyncSpinner spinner(1);
    spinner.start();

    //setup
    static const std::string PLANNING_GROUP = "panda_arm";//panda // group name 不能随意写,要和srdf中的group name 一致
    moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);

    // robot_state = moveit::core
    const robot_state::JointModelGroup *joint_model_group = move_group.getCurrentState()->getJointModelGroup(
            PLANNING_GROUP);


    //moveit::planning_interface::PlanningSceneInterface planningSceneInterface;

    //visualTools
    moveit_visual_tools::MoveItVisualTools visualTools("panda_link0");//panda
    visualTools.deleteAllMarkers();
    visualTools.loadRemoteControl();


    //加上文字
    Eigen::Isometry3d text_pose = Eigen::Isometry3d::Identity(); // 3dim double 变换矩阵
    std::cout << text_pose.matrix() << std::endl;
    text_pose.translation().z() = 1.05;
    std::cout << text_pose.matrix() << std::endl;
    namespace rvt = rviz_visual_tools;
    visualTools.publishText(text_pose, "move group c++ interface demo by zcb", rvt::WHITE, rvt::XLARGE);
    visualTools.trigger();

    //打印相关的信息
    ROS_INFO("Planning frame: %s", move_group.getPlanningFrame().c_str());
    ROS_INFO("End effector link: %s", move_group.getEndEffectorLink().c_str());
    ROS_INFO("Available Planning Groups: ");
    std::vector<std::string> groups = move_group.getJointModelGroupNames();
    for (auto &name : groups) {
        std::cout << name << "\n---" << std::endl;
    }

    //等待用户 点击
    visualTools.prompt("Press 'next' in the RvizVisualToolsGui window to start the demo");

    // =================================================================
    // Planning to a Pose goal
    geometry_msgs::Pose target_pose1;
    target_pose1.orientation.w = 1;
    target_pose1.position.x = 0.28;
    target_pose1.position.y = -0.2;
    target_pose1.position.z = 0.5;
    move_group.setPoseTarget(target_pose1);

    //对上面的目标位置 进行规划(显示移动)
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    moveit::planning_interface::MoveItErrorCode code = move_group.plan(my_plan);
    bool success = (code == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    ROS_INFO("Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");

    //保留移动轨迹
    ROS_INFO("Visualizing plan 1 as trajectory line");
    visualTools.publishAxisLabeled(target_pose1, "pose1 coor"); // 建立坐标系
    visualTools.publishText(text_pose, "Pose Goal", rvt::WHITE, rvt::XLARGE);// 文字
    visualTools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);// 显示轨迹
    visualTools.trigger();
    visualTools.prompt("Press 'next' in the RvizVisualToolsGui window to continue the demo");

    // 真正的移动
    // Uncomment below line when working with a real robot
    //move_group.move();

    // =================================================================
    // Planning to a joint-space goal
    moveit::core::RobotStatePtr currentState = move_group.getCurrentState();
    std::vector<double> joint_group_positions;
    currentState->copyJointGroupPositions(joint_model_group, joint_group_positions);
//    for(auto &pos:joint_group_positions){ // 关节的的角度位置
//        std::cout <<pos<<"\n---"<< std::endl;
//    }
    joint_group_positions[0] = -1.0;  // radians
    move_group.setJointValueTarget(joint_group_positions); // 设置目标 joint

    //规划（显示移动）
    success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    ROS_INFO("Visualizing plan 2 (joint space goal) %s", success ? "" : "FAILED");

    //显示轨迹
    visualTools.deleteAllMarkers();
    visualTools.publishText(text_pose, "Joint Space Goal", rvt::WHITE, rvt::XLARGE);
    visualTools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
    visualTools.trigger();
    visualTools.prompt("Press 'next' in the RvizVisualToolsGui window to continue the demo");

    // =================================================================
    // Planning with Path Constraints,约束link
    moveit_msgs::OrientationConstraint ocm;
    ocm.link_name = "panda_link7"; // 要约束的目标 panda_link7
    ocm.header.frame_id = "panda_link0"; // 相对参考的 坐标系,link0 的坐标系,一般都是基座坐标系
    ocm.orientation.w = 1.0;
    ocm.absolute_x_axis_tolerance = 0.1; // 轴角 error tolerance,误差范围
    ocm.absolute_y_axis_tolerance = 0.1;
    ocm.absolute_z_axis_tolerance = 0.1;
    ocm.weight = 1.0; // 权重 相对其他约束的重要性

    moveit_msgs::Constraints test_constraints;
    test_constraints.orientation_constraints.push_back(ocm);// 也可以有对其他 link的约束
    move_group.setPathConstraints(test_constraints);  // 设置path constraints

    //创建一个 开始的状态
    robot_state::RobotState start_state(*move_group.getCurrentState());
    geometry_msgs::Pose start_pose;
    start_pose.orientation.w = 1.0;
    start_pose.position.x = 0.55;
    start_pose.position.y = -0.05;
    start_pose.position.z = 0.8;
    start_state.setFromIK(joint_model_group, start_pose);
    move_group.setStartState(start_state);

    // 从开始的状态 移动到 之前的 target_pose1
    move_group.setPoseTarget(target_pose1);
    move_group.setPlanningTime(10.0);//
    // 规划（显示移动）
    success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    ROS_INFO_NAMED("tutorial", "Visualizing plan 3 (constraints) %s", success ? "" : "FAILED");
    // 保留轨迹
    visualTools.deleteAllMarkers();
    visualTools.publishAxisLabeled(start_pose, "start");
    visualTools.publishAxisLabeled(target_pose1, "goal");
    visualTools.publishText(text_pose, "Constrained Goal", rvt::WHITE, rvt::XLARGE);
    visualTools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
    visualTools.trigger();
    visualTools.prompt("next step");
    // clear path constraints
    move_group.clearPathConstraints();


    // =================================================================
    // Cartesian Paths,沿着自己选定的点走
    std::vector<geometry_msgs::Pose> waypoints;
    waypoints.push_back(start_pose);

    geometry_msgs::Pose target_pose2 = start_pose;

    target_pose2.position.z -= 0.2;
    waypoints.push_back(target_pose2);  // down

    target_pose2.position.y -= 0.2;
    waypoints.push_back(target_pose2);  // right

    target_pose2.position.z += 0.2;
    target_pose2.position.y += 0.2;
    target_pose2.position.x -= 0.2;
    waypoints.push_back(target_pose2);  // up and left

    move_group.setMaxVelocityScalingFactor(0.1);

    moveit_msgs::RobotTrajectory trajectory;
    const double jump_threshold = 0.0;
    const double eef_step = 0.01;
    double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
    ROS_INFO("Visualizing plan 4 (Cartesian path) (%.2f%% acheived)", fraction * 100.0);

    visualTools.deleteAllMarkers();
    visualTools.publishText(text_pose, "Cartesian Paths", rvt::WHITE, rvt::XLARGE);
    visualTools.publishPath(waypoints, rvt::LIME_GREEN, rvt::SMALL);
    for (std::size_t i = 0; i < waypoints.size(); ++i)
        visualTools.publishAxisLabeled(waypoints[i], "pt" + std::to_string(i), rvt::SMALL);
    visualTools.trigger();

    moveit::planning_interface::PlanningSceneInterface planningSceneInterface;//下面 增加障碍物使用(这个位置以上都可以)
    visualTools.prompt("Press 'next' in the RvizVisualToolsGui window to continue the demo");
    //moveit::planning_interface::PlanningSceneInterface planningSceneInterface;//下面 增加障碍物使用(这个位置不行)

    // =========================================================================
    // Adding/Removing Objects and Attaching/Detaching Objects

    moveit_msgs::CollisionObject collision_object; // 障碍物
    collision_object.header.frame_id = move_group.getPlanningFrame();// 障碍物参考的坐标系 (world)
    collision_object.id = "box1";

    shape_msgs::SolidPrimitive primitive;
    primitive.type = primitive.BOX;
    primitive.dimensions.resize(3);
    primitive.dimensions[0] = 0.4;
    primitive.dimensions[1] = 0.1;
    primitive.dimensions[2] = 0.4;

    geometry_msgs::Pose box_pose; // relative to frame_id
    box_pose.orientation.w = 1.0;
    box_pose.position.x = 0.4;
    box_pose.position.y = -0.2;
    box_pose.position.z = 1.0;

    collision_object.primitives.push_back(primitive);
    collision_object.primitive_poses.push_back(box_pose);
    collision_object.operation = collision_object.ADD;

    std::vector<moveit_msgs::CollisionObject> collision_objects;
    collision_objects.push_back(collision_object);

    ROS_INFO("Add an object into the world");
    planningSceneInterface.addCollisionObjects(collision_objects);

    visualTools.publishText(text_pose, "Add collision object", rvt::WHITE, rvt::XLARGE);
    visualTools.trigger(); // 显示障碍物
    visualTools.prompt("Press 'next' in the RvizVisualToolsGui window to once the collision object appears in RViz");

    move_group.setStartState(*move_group.getCurrentState());
    geometry_msgs::Pose another_pose;
    another_pose.orientation.w = 1.0;
    another_pose.position.x = 0.4;
    another_pose.position.y = -0.4;
    another_pose.position.z = 0.9;
    move_group.setPoseTarget(another_pose);
    // 显示移动
    success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    ROS_INFO("Visualizing plan 5 (pose goal move around cuboid) %s", success ? "" : "FAILED");
    // 保留轨迹
    visualTools.deleteAllMarkers();
    visualTools.publishText(text_pose, "Obstacle Goal", rvt::WHITE, rvt::XLARGE);
    visualTools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
    visualTools.trigger();
    visualTools.prompt("next step");

    ROS_INFO("Attach the object to the robot");
    move_group.attachObject(collision_object.id);
    visualTools.publishText(text_pose, "Object attached to robot", rvt::WHITE, rvt::XLARGE);
    visualTools.trigger();
    // Wait for MoveGroup to recieve and process the attached collision object message
    visualTools.prompt("Press 'next' in the RvizVisualToolsGui window to once the collision object attaches to the "
                        "robot");

    ROS_INFO("Detach the object from the robot");
    move_group.detachObject(collision_object.id);
    visualTools.publishText(text_pose, "Object dettached from robot", rvt::WHITE, rvt::XLARGE);
    visualTools.trigger();
    // Wait for MoveGroup to recieve and process the attached collision object message
    visualTools.prompt("Press 'next' in the RvizVisualToolsGui window to once the collision object detaches to the "
                        "robot");

    // remove the collision object from the world
    ROS_INFO("Remove the object from the world");
    std::vector<std::string> object_ids;
    object_ids.push_back(collision_object.id);
    planningSceneInterface.removeCollisionObjects(object_ids);

    visualTools.publishText(text_pose, "Object removed", rvt::WHITE, rvt::XLARGE);
    visualTools.trigger();
    // Wait for MoveGroup to recieve and process the attached collision object message
    visualTools.prompt("Press 'next' in the RvizVisualToolsGui window to once the collision object disapears");


    // Wait for this node to be shutdown, whether through Ctrl-C, ros::shutdown(), or similar.
    //ros::waitForShutdown();


    return 0;

}

