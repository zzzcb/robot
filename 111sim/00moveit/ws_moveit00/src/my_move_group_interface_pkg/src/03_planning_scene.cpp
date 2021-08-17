//
// Created by zcb on 6/22/21.
//
/*
 * planning scene
 * http://docs.ros.org/en/melodic/api/moveit_tutorials/html/doc/planning_scene/planning_scene_tutorial.html
 */

#include <ros/ros.h>
// MoveIt
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/planning_scene/planning_scene.h>// for PlanningScene

#include <moveit/kinematic_constraints/utils.h>

bool stateFeasibilityTestExample(const robot_state::RobotState &kinematic_state, bool verbose) {
    const double *joint_values = kinematic_state.getJointPositions("panda_joint1");
    return (joint_values[0] > 0.0);
}

int main(int argc, char **argv) {
    //1 初始化节点
    ros::init(argc, argv, "panda_arm_kinematics");
    ros::AsyncSpinner spinner(1);
    spinner.start();
    int count = 0;

    //2 setup:
    //注意:
    //The PlanningScene class can be easily setup and configured using a RobotModel or a URDF and SRDF.
    //This is, however, not the recommended way to instantiate a PlanningScene.
    //The PlanningSceneMonitor is the recommended method to create and maintain the current
    //planning scene (and is discussed in detail in the next tutorial)
    //using data from the robot’s joints and the sensors on the robot.
    //In this tutorial, we will instantiate a PlanningScene class directly,
    //but this method of instantiation is only intended for illustration.
    robot_model_loader::RobotModelLoader robot_model_loader("robot_description");
    robot_model::RobotModelPtr kinematic_model = robot_model_loader.getModel();
    planning_scene::PlanningScene planning_scene(kinematic_model);//使用model初始化scene并不好,这里只是为了演示

    //3 Collision Checking
    //3.1 Self-collision checking
    //To do this, we will construct a CollisionRequest object and a CollisionResult object
    //and pass them into the collision checking function.
    //Note that the result of whether the robot is in self-collision or not is contained within the result.
    //Self collision checking uses an unpadded version of the robot,
    // i.e. it directly uses the collision meshes provided in the URDF with no extra padding added on.

    collision_detection::CollisionRequest collision_request;
    collision_detection::CollisionResult collision_result;
    // Check whether the current state is in self collision
    planning_scene.checkSelfCollision(collision_request, collision_result);
    ROS_INFO_STREAM("Test 1: Current state is " << (collision_result.collision ? "in" : "not in") << " self collision");

    //change the state
    robot_state::RobotState &current_state = planning_scene.getCurrentStateNonConst();
    current_state.setToRandomPositions(); // 随机的值,所以可能会 self-collision
    collision_result.clear(); //Note in particular that we need to clear the collision_result before making a new collision checking request.
    planning_scene.checkSelfCollision(collision_request, collision_result);
    ROS_INFO_STREAM("Test 2: Current state is " << (collision_result.collision ? "in" : "not in") << " self collision");

    //3.2 Checking for a group
    //i.e. we will check whether there are any collisions between the hand and other parts of the body of the robot.
    collision_request.group_name = "hand";
    current_state.setToRandomPositions();
    collision_result.clear();
    planning_scene.checkSelfCollision(collision_request, collision_result);
    ROS_INFO_STREAM("Test 3: Current state is " << (collision_result.collision ? "in" : "not in") << " self collision");

    //3.3 Getting Contact Information 获取详细的 碰撞信息
    //manually set the Panda arm to a position where we know internal (self) collisions do happen.
    //Note that this state is now actually outside the joint limits of the Panda, which we can also check for directly.

    std::vector<double> joint_values = {0.0, 0.0, 0.0, -2.9, 0.0, 1.4, 0.0};
    const robot_model::JointModelGroup *joint_model_group = current_state.getJointModelGroup("panda_arm");
    current_state.setJointGroupPositions(joint_model_group, joint_values);
    ROS_INFO_STREAM(
            "Test 4: Current state is " << (current_state.satisfiesBounds(joint_model_group) ? "valid" : "not valid"));

    collision_request.contacts = true;
    collision_request.max_contacts = 1000;

    collision_result.clear();
    planning_scene.checkSelfCollision(collision_request, collision_result);
    ROS_INFO_STREAM("Test 5: Current state is " << (collision_result.collision ? "in" : "not in") << " self collision");
    collision_detection::CollisionResult::ContactMap::const_iterator it;
    for (it = collision_result.contacts.begin(); it != collision_result.contacts.end(); ++it) {
        ROS_INFO("Contact between: %s and %s", it->first.first.c_str(), it->first.second.c_str());
    }
    //3.4 Modifying the Allowed Collision Matrix
    // The AllowedCollisionMatrix (ACM) provides a mechanism to tell
    // the collision world to ignore collisions between certain object:
    // both parts of the robot and objects in the world.
    collision_detection::AllowedCollisionMatrix acm = planning_scene.getAllowedCollisionMatrix();
    robot_state::RobotState copied_state = planning_scene.getCurrentState();

    collision_detection::CollisionResult::ContactMap::const_iterator it2;
    for (it2 = collision_result.contacts.begin(); it2 != collision_result.contacts.end(); ++it2) {
        acm.setEntry(it2->first.first, it2->first.second, true); // 这样修改后,如果再次检测就不会碰撞了
        std::cout << "--- item ---" << std::endl;
    }
    collision_result.clear();
    planning_scene.checkSelfCollision(collision_request, collision_result, copied_state, acm);
    ROS_INFO_STREAM("Test 6: Current state is " << (collision_result.collision ? "in" : "not in") << " self collision");

    //4 Full Collision Checking
    // While we have been checking for self-collisions, we can use the
    // checkCollision functions instead which will check for both
    // self-collisions and for collisions with the environment (which is
    // currently empty).  This is the set of collision checking
    // functions that you will use most often in a planner. Note that
    // collision checks with the environment will use the padded version
    // of the robot. Padding helps in keeping the robot further away
    // from obstacles in the environment.

    collision_result.clear();
    planning_scene.checkCollision(collision_request, collision_result, copied_state, acm);
    ROS_INFO_STREAM("Test 7: Current state is " << (collision_result.collision ? "in" : "not in") << " self collision");

    //5 Constraint Checking
    // The PlanningScene class also includes easy to use function calls
    // for checking constraints. The constraints can be of two types:
    // (a) constraints chosen from the
    //  KinematicConstraint set:
    //      JointConstraint
    //      PositionConstraint
    //      OrientationConstraint
    //      VisibilityConstraint
    // (b) user defined constraints specified through a callback.

    //5.1 Checking Kinematic Constraints
    // We will first define a simple position and orientation constraint
    // on the end-effector of the panda_arm group of the Panda robot. Note the
    // use of convenience functions for filling up the constraints
    // (these functions are found in the :moveit_core_files:utils.h file from the
    // kinematic_constraints directory in moveit_core).

    std::string end_effector_name = joint_model_group->getLinkModelNames().back();

    geometry_msgs::PoseStamped desired_pose;
    desired_pose.pose.orientation.w = 1.0;
    desired_pose.pose.position.x = 0.3;
    desired_pose.pose.position.y = -0.185;
    desired_pose.pose.position.z = 0.5;
    desired_pose.header.frame_id = "panda_link0";
    // kinematic_constraints 定义在 moveit/kinematic_constraints/utils.h 中
    moveit_msgs::Constraints goal_constraint =
            kinematic_constraints::constructGoalConstraints(end_effector_name, desired_pose);

    copied_state.setToRandomPositions();
    copied_state.update();
    bool constrained = planning_scene.isStateConstrained(copied_state, goal_constraint);
    ROS_INFO_STREAM("Test 8: Random state is " << (constrained ? "constrained" : "not constrained"));

    // There’s a more efficient way of checking constraints (when you want
    // to check the same constraint over and over again)

    kinematic_constraints::KinematicConstraintSet kinematic_constraint_set(kinematic_model);// 多个约束的集合
    kinematic_constraint_set.add(goal_constraint, planning_scene.getTransforms()); // add ...
    bool constrained_2 = planning_scene.isStateConstrained(copied_state, kinematic_constraint_set);
    ROS_INFO_STREAM("Test 9: Random state is " << (constrained_2 ? "constrained" : "not constrained"));

    // There’s a direct way to do this using the KinematicConstraintSet class
    kinematic_constraints::ConstraintEvaluationResult constraint_eval_result =
            kinematic_constraint_set.decide(copied_state);
    ROS_INFO_STREAM("Test 10: Random state is "
                            << (constraint_eval_result.satisfied ? "constrained" : "not constrained"));




    //5.2 User-defined constraints
    //User defined constraints can also be specified to the PlanningScene class.
    // This is done by specifying a callback using the setStateFeasibilityPredicate function.
    // Here’s a simple example of a user-defined callback that checks
    // whether the “panda_joint1” of the Panda robot is at a positive or negative angle:

    planning_scene.setStateFeasibilityPredicate(stateFeasibilityTestExample);
    bool state_feasible = planning_scene.isStateFeasible(copied_state);//此时会 调用stateFeasibility回调函数
    ROS_INFO_STREAM("Test 11: Random state is " << (state_feasible ? "feasible" : "not feasible"));

    //其他
    //Whenever isStateValid is called, three checks are conducted:
    // (a) collision checking
    // (b) constraint checking
    // (c) feasibility checking using the user-defined callback.
    bool state_valid = planning_scene.isStateValid(copied_state, kinematic_constraint_set, "panda_arm");
    ROS_INFO_STREAM("Test 12: Random state is " << (state_valid ? "valid" : "not valid"));

    ros::shutdown();

    return 0;
}