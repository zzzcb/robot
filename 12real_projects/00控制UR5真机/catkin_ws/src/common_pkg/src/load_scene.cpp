#include <iostream>

// ros
#include <ros/ros.h>

// MoveIt
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>


const std::string ARM_GROUP = "manipulator";
const float BOX_X = 0.2;
const float BOX_Y = 0.2;
const float BOX_Z = 0.2;
const float BOX_POS_X = -0.5;
const float BOX_POS_Y = 0.5;
const float BOX_POS_Z = 0.5;

void add_box(moveit::planning_interface::MoveGroupInterface &group,
              moveit::planning_interface::PlanningSceneInterface &scene) {

    //1 添加一个box 
    std::vector<moveit_msgs::CollisionObject> objects;
    objects.resize(1); 

    //2 对 objects[0] 进行基础设置
    objects[0].id = "box";
    objects[0].operation = objects[0].ADD;
    objects[0].header.frame_id = group.getPlanningFrame();

    // 形状信息
    objects[0].primitives.resize(1); // 只有一个primitive
    objects[0].primitives[0].type = objects[0].primitives[0].BOX;
    objects[0].primitives[0].dimensions.resize(3); // 3 个维度
    objects[0].primitives[0].dimensions[0] = BOX_X; // box 的x y z 长度
    objects[0].primitives[0].dimensions[1] = BOX_Y;
    objects[0].primitives[0].dimensions[2] = BOX_Z;

    // 位姿信息
    geometry_msgs::Pose pose;
    pose.position.x = BOX_POS_X;
    pose.position.y = BOX_POS_Y;
    pose.position.z = BOX_POS_Z + BOX_Z / 2;
    pose.orientation.w = 1.0;
    pose.orientation.x = 0.0;
    pose.orientation.y = 0.0;
    pose.orientation.z = 0.0;

    objects[0].primitive_poses.resize(1); // 只有一个 primitive
    objects[0].primitive_poses[0].position = pose.position;
    objects[0].primitive_poses[0].orientation = pose.orientation;


    //3 加入到场景中
    scene.addCollisionObjects(objects);
}

int main(int argc,char** argv){

    //1 初始化节点
    ros::init(argc, argv, "load_scene");
    ros::NodeHandle nh;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    //2 setup
    moveit::planning_interface::MoveGroupInterface armGroup(ARM_GROUP);
    std::string armPlanningFrame = armGroup.getPlanningFrame();
    moveit_visual_tools::MoveItVisualTools mvt(armPlanningFrame);

    moveit::planning_interface::PlanningSceneInterface scene;

    //3 一上来先删除 box,方便循环调试
    mvt.prompt("remove box");
    std::vector<std::string> ids = {"box"};
    scene.removeCollisionObjects(ids);

    //4 添加障碍物
    mvt.prompt("add box");
    add_box(armGroup, scene);


    mvt.prompt("done");

    return 0;
}

