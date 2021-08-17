//
// Created by zcb on 6/22/21.
//

/*
 * robot_model 和 robot_state
 * http://docs.ros.org/en/melodic/api/moveit_tutorials/html/doc/robot_model_and_robot_state/robot_model_and_robot_state_tutorial.html
 */
#include <ros/ros.h>

// MoveIt
#include <moveit/robot_model_loader/robot_model_loader.h> // for load model from param server
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>

int main(int argc, char **argv) {
    //1 初始化节点
    ros::init(argc, argv, "zcb_robot_model_and_robot_state");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    //2 RobotModelLoader(它从param server中加载模型 构建RobotModel出来)
    robot_model_loader::RobotModelLoader modelLoader("robot_description");
    moveit::core::RobotModelPtr kinematic_model = modelLoader.getModel();
    ROS_INFO("Model Frame: %s", kinematic_model->getModelFrame().c_str());

    //3 使用RobotModel 构建 RobotState
    robot_state::RobotStatePtr kinematic_state(new robot_state::RobotState(kinematic_model));
    kinematic_state->setToDefaultValues(); // set all joints to their default values

    moveit::core::JointModelGroup *joint_model_group = kinematic_model->getJointModelGroup("panda_arm");

    //4 得到该group中所有的joint name
    const std::vector<std::string> &joint_names = joint_model_group->getVariableNames(); // 返回该 group中的所有joint 名字

    //5 得到该group中所有的joint value
    std::vector<double> joint_values;
    kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);

    //打印4 和 5
    for (int i = 0; i < joint_names.size(); ++i) {
        ROS_INFO("in panda_arm group, joint name: %s ,joint value: %f", joint_names[i].c_str(), joint_values[i]);
    }

    //6 joint limits
    joint_values[0] = 5.57;
    kinematic_state->setJointGroupPositions(joint_model_group, joint_values); // 给这个group 设置position(joint values)

    // setJointGroupPositions() does not enforce joint limits by itself, but a call to enforceBounds() will do it.
    // Check whether any joint is outside its joint limits
    ROS_INFO_STREAM("Current state is " << (kinematic_state->satisfiesBounds() ? "valid" : "not valid"));

    // Enforce the joint limits for this state and check again
    kinematic_state->enforceBounds();
    ROS_INFO_STREAM("Current state is " << (kinematic_state->satisfiesBounds() ? "valid" : "not valid"));

    // 此时的 joint_values
    kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);
    for (int i = 0; i < joint_names.size(); ++i) {
        ROS_INFO("after random and after limit, joint name: %s ,joint value: %f", joint_names[i].c_str(), joint_values[i]);
    }

    //7 forward kinematics 正向运动学
    // Note :“panda_link8” is the most distal link in the “panda_arm” group
    kinematic_state->setToRandomPositions(joint_model_group); // 设置group 为 随机姿态
    const Eigen::Isometry3d &end_effector_state = kinematic_state->getGlobalLinkTransform("panda_link8");
    ROS_INFO_STREAM("4x4 Transform Matrix: \n" << end_effector_state.matrix());

    //8 inverse kinematics 反向运动学
    double timeout = 0.1;
    bool found_ik = kinematic_state->setFromIK(joint_model_group, end_effector_state, timeout);
    if (found_ik) {
        ROS_INFO("Find IK solution:\n");
        kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);
        for (int i = 0; i < joint_names.size(); ++i) {
            ROS_INFO("joint name: %s,joint value:%f", joint_names[i].c_str(), joint_values[i]);
        }
    } else {
        ROS_INFO("Did not find IK solution");
    }
    //9 Get the Jacobian
    Eigen::Vector3d reference_point_position(0.0, 0.0, 0.0);
    Eigen::MatrixXd jacobian;
    kinematic_state->getJacobian(joint_model_group,
                                 kinematic_state->getLinkModel(joint_model_group->getLinkModelNames().back()),
                                 reference_point_position, jacobian);
    ROS_INFO_STREAM("Jacobian: \n" << jacobian << "\n");

    ros::shutdown();

    return 0;
}