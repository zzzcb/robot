//
// Created by zcb on 6/19/21.
//
/*
 * 参考:
 * http://robot.czxy.com/docs/kinematics/moveit/panda/
 */
#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
#include <tf/tf.h>


int main(int argc, char **argv) {
    //1 初始化 节点
    std::string nodeName = "move_group_cpp_interface";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    //2 setup
    static const std::string PLANNING_GROUP = "panda_arm";
    moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
    moveit::planning_interface::PlanningSceneInterface scene;
    const robot_state::JointModelGroup *joint_model_group = move_group.getCurrentState()->getJointModelGroup(
            PLANNING_GROUP);
    //visualTools
    moveit_visual_tools::MoveItVisualTools visualTools("panda_link0");//panda
    visualTools.deleteAllMarkers();
    visualTools.loadRemoteControl();

    const std::string &frame = move_group.getPlanningFrame();

    //3 添加桌子1,桌子2,待夹取物
    std::vector<moveit_msgs::CollisionObject> objects;
    moveit_msgs::CollisionObject obj;

    //桌子1
    obj.id = "desk01";
    obj.operation = obj.ADD;
    obj.header.frame_id = frame;
    //桌子1形状
    shape_msgs::SolidPrimitive primitive;
    primitive.type = primitive.BOX;//矩形，长宽高
    primitive.dimensions.resize(3);
    primitive.dimensions[0] = 0.2;
    primitive.dimensions[1] = 0.4;
    primitive.dimensions[2] = 0.4;
    obj.primitives.push_back(primitive);
    //桌子1的位姿
    geometry_msgs::Pose pose;
    pose.position.x = 0.5;
    pose.position.y = 0;
    pose.position.z = 0.2;
    pose.orientation.w = 1;
    obj.primitive_poses.push_back(pose);
    objects.push_back(obj);

    //桌子2
    obj.id = "desk02";
    obj.operation = obj.ADD;
    obj.header.frame_id = frame;
    //桌子2形状
    primitive.type = primitive.BOX;//矩形，长宽高
    primitive.dimensions.resize(3);
    primitive.dimensions[0] = 0.4;
    primitive.dimensions[1] = 0.2;
    primitive.dimensions[2] = 0.4;
    obj.primitives.push_back(primitive);
    //桌子2的位姿
    pose.position.x = 0;
    pose.position.y = 0.5;
    pose.position.z = 0.2;
    pose.orientation.w = 1;
    obj.primitive_poses.push_back(pose);
    objects.push_back(obj);

    //待夹取物
    obj.id = "obj";
    obj.operation = obj.ADD;
    obj.header.frame_id = frame;
    //物体形状
    primitive.type = primitive.BOX;//矩形，长宽高
    primitive.dimensions.resize(3);
    primitive.dimensions[0] = 0.02;
    primitive.dimensions[1] = 0.02;
    primitive.dimensions[2] = 0.2;
    obj.primitives.push_back(primitive);
    //物体位姿
    pose.position.x = 0.5;
    pose.position.y = 0;
    pose.position.z = 0.5;
    pose.orientation.w = 1;
    obj.primitive_poses.push_back(pose);
    objects.push_back(obj);

    scene.addCollisionObjects(objects);
    visualTools.trigger();
    visualTools.prompt("press next to grasp");

    //4 夹取物体
    std::vector<moveit_msgs::Grasp> grasps;

    moveit_msgs::Grasp grasp; //grasp pose
    //设置位姿参考坐标系
    grasp.grasp_pose.header.frame_id = frame;
    //设置位姿
    grasp.grasp_pose.pose.position.x = 0.4;
    grasp.grasp_pose.pose.position.y = 0;
    grasp.grasp_pose.pose.position.z = 0.5;
    tf::Quaternion quat;
    quat.setRPY(-1.57, -0.785, -1.57);
    grasp.grasp_pose.pose.orientation.x = quat.x();
    grasp.grasp_pose.pose.orientation.y = quat.y();
    grasp.grasp_pose.pose.orientation.z = quat.z();
    grasp.grasp_pose.pose.orientation.w = quat.w();
    //夹取物体之前,沿着x轴方向靠近
    grasp.pre_grasp_approach.direction.header.frame_id = frame;
    grasp.pre_grasp_approach.direction.vector.x = 1.0;
    grasp.pre_grasp_approach.min_distance = 0.095;
    grasp.pre_grasp_approach.desired_distance = 0.115;
    //打开夹爪
    grasp.pre_grasp_posture.joint_names.resize(2);
    grasp.pre_grasp_posture.joint_names[0] = "panda_finger_joint1";
    grasp.pre_grasp_posture.joint_names[1] = "panda_finger_joint2";
    //两个手指向外移动（0-0.04）
    grasp.pre_grasp_posture.points.resize(1);
    grasp.pre_grasp_posture.points[0].positions.resize(2);
    grasp.pre_grasp_posture.points[0].positions[0] = 0.04;
    grasp.pre_grasp_posture.points[0].positions[1] = 0.04;
    grasp.pre_grasp_posture.points[0].time_from_start = ros::Duration(0.5);
    //关闭夹爪
    grasp.grasp_posture.joint_names.resize(2);
    grasp.grasp_posture.joint_names[0] = "panda_finger_joint1";
    grasp.grasp_posture.joint_names[1] = "panda_finger_joint2";
    //两个手指向内（0-0.04）
    grasp.grasp_posture.points.resize(1);
    grasp.grasp_posture.points[0].positions.resize(2);
    grasp.grasp_posture.points[0].positions[0] = 0.04;
    grasp.grasp_posture.points[0].positions[1] = 0.04;
    grasp.grasp_posture.points[0].time_from_start = ros::Duration(0.5);
    //夹取后,沿着Z轴方向离开
    grasp.post_grasp_retreat.direction.header.frame_id = frame;
    grasp.post_grasp_retreat.direction.vector.z = 1.0;
    grasp.post_grasp_retreat.min_distance = 0.1;
    grasp.post_grasp_retreat.desired_distance = 0.25;

    //进行夹取
    grasps.push_back(grasp);
    move_group.pick("obj", grasps);


    visualTools.prompt("next step");

    return 0;

}

