#! /usr/bin/env python
# coding:utf8
"""
参考: http://docs.ros.org/en/melodic/api/moveit_tutorials/html/doc/move_group_python_interface/move_group_python_interface_tutorial.html#
"""
import rospy
import moveit_commander  # for MoveGroupCommander PlanningSceneInterface RobotCommander
import sys
import moveit_msgs.msg
from math import pi
import geometry_msgs.msg
from moveit_commander.conversions import pose_to_list
import copy


def all_close(goal, actual, tolerance):
    """
    Convenience method for testing if a list of values are within a toleranc    e of their counterparts in another list
    @param: goal       A list of floats, a Pose or a PoseStamped
    @param: actual     A list of floats, a Pose or a PoseStamped
    @param: tolerance  A float
    @returns: bool
    """
    all_equal = True
    if type(goal) is list:
        for index in range(len(goal)):
            if abs(actual[index] - goal[index]) > tolerance:
                return False

    elif type(goal) is geometry_msgs.msg.PoseStamped:
        return all_close(goal.pose, actual.pose, tolerance)

    elif type(goal) is geometry_msgs.msg.Pose:
        return all_close(pose_to_list(goal), pose_to_list(actual), tolerance)

    return True


class MyMoveGroupInterface:
    def __init__(self):
        # 1 init
        moveit_commander.roscpp_initialize(sys.argv)
        node_name = "move_group_py_interface"
        rospy.init_node(node_name, anonymous=True)

        # move_group can be used to plan and execute motions
        group_name = "panda_arm"
        move_group = moveit_commander.MoveGroupCommander(group_name)

        # robot's kinematic model | robot's cur joint state
        robot = moveit_commander.RobotCommander()
        # a remote interface for getting, setting, and updating the robot’s internal understanding of the surrounding world
        scene = moveit_commander.PlanningSceneInterface()

        # 向 /move_group/display_planned_path 这个topic 发布消息
        display_trajectory_publisher = rospy.Publisher("/move_group/display_planned_path",
                                                       moveit_msgs.msg.DisplayTrajectory,
                                                       queue_size=20)
        # 2 basic information
        # We can get the name of the reference frame for this robot:
        planning_frame = move_group.get_planning_frame()
        print "============ Planning frame: %s" % planning_frame

        # We can also print the name of the end-effector link for this group:
        eef_link = move_group.get_end_effector_link()
        print "============ End effector link: %s" % eef_link

        # We can get a list of all the groups in the robot:
        group_names = robot.get_group_names()
        print "============ Available Planning Groups:", robot.get_group_names()

        # Sometimes for debugging it is useful to print the entire state of the
        # robot:
        print "============ Printing robot state"
        print robot.get_current_state()
        print ""

        # 3 Misc(杂项) variables
        self.box_name = ''
        self.robot = robot
        self.scene = scene
        self.move_group = move_group
        self.display_trajectory_publisher = display_trajectory_publisher
        self.planning_frame = planning_frame
        self.eef_link = eef_link
        self.group_names = group_names

    def go_to_joint_state(self):
        move_group = self.move_group

        # 先移动到一个 舒服的位置
        joint_goal = move_group.get_current_joint_values()
        joint_goal[0] = 0
        joint_goal[1] = -pi / 4
        joint_goal[2] = 0
        joint_goal[3] = -pi / 2
        joint_goal[4] = 0
        joint_goal[5] = pi / 3
        joint_goal[6] = 0

        # 内部参数 wait,默认是 True,即默认是同步的
        move_group.go(joint_goal)

        # Calling ``stop()`` ensures that there is no residual movement
        move_group.stop()

        # 判断 每个关节角度是否 符合精度要求
        current_joints = move_group.get_current_joint_values()
        return all_close(joint_goal, current_joints, 0.01)

    def go_to_pose_goal(self):
        move_group = self.move_group

        pose_goal = geometry_msgs.msg.Pose()
        pose_goal.orientation.w = 1.0
        pose_goal.position.x = 0.4
        pose_goal.position.y = 0.1
        pose_goal.position.z = 0.4

        move_group.set_pose_target(pose_goal)

        plan = move_group.go()
        # Calling `stop()` ensures that there is no residual movement
        move_group.stop()
        # It is always good to clear your targets after planning with poses.
        # Note: there is no equivalent function for clear_joint_value_targets()
        move_group.clear_pose_targets()

        current_pose = self.move_group.get_current_pose().pose
        return all_close(pose_goal, current_pose, 0.01)

    def plan_cartesian_path(self, scale=1.0):
        move_group = self.move_group

        waypoints = []

        wpose = move_group.get_current_pose().pose
        wpose.position.z -= scale * 0.1  # First move up (z)
        wpose.position.y += scale * 0.2  # and sideways (y)
        waypoints.append(copy.deepcopy(wpose))

        wpose.position.x += scale * 0.1  # Second move forward/backwards in (x)
        waypoints.append(copy.deepcopy(wpose))

        wpose.position.y -= scale * 0.1  # Third move sideways (y)
        waypoints.append(copy.deepcopy(wpose))

        # We want the Cartesian path to be interpolated at a resolution of 1 cm
        # which is why we will specify 0.01 as the eef_step in Cartesian
        # translation.  We will disable the jump threshold by setting it to 0.0,
        # ignoring the check for infeasible jumps in joint space, which is sufficient
        # for this tutorial.

        # plan 规划
        # fraction 匹配路径的分数
        (plan, fraction) = move_group.compute_cartesian_path(
            waypoints,  # waypoints to follow
            0.01,  # eef_step
            0.0)  # jump_threshold

        print "%.2f%% acheived" % (fraction * 100.0)
        # Note: We are just planning, not asking move_group to actually move the robot yet:
        return plan, fraction

    def execute_plan(self, plan):
        move_group = self.move_group
        move_group.execute(plan)
        # Note: The robot’s current joint state must be within some tolerance of the first waypoint in the RobotTrajectory or execute() will fail

    def display_trajectory(self, plan):
        robot = self.robot
        display_trajectory_publisher = self.display_trajectory_publisher

        display_trajectory = moveit_msgs.msg.DisplayTrajectory()
        display_trajectory.trajectory_start = robot.get_current_state()
        display_trajectory.trajectory.append(plan)
        # Publish
        display_trajectory_publisher.publish(display_trajectory)

    """
    是否状态更新完成
    """

    def wait_for_state_update(self, box_is_known=False, box_is_attached=False, timeout=4):
        box_name = self.box_name
        scene = self.scene

        start = rospy.get_time()
        seconds = rospy.get_time()
        while (seconds - start < timeout) and not rospy.is_shutdown():
            # Test if the box is in attached objects
            attached_objects = scene.get_attached_objects([box_name])
            is_attached = len(attached_objects.keys()) > 0

            # Test if the box is in the scene.
            # Note that attaching the box will remove it from known_objects
            is_known = box_name in scene.get_known_object_names()

            if (box_is_attached == is_attached) and (box_is_known == is_known):
                return True
            rospy.sleep(0.1)
            seconds = rospy.get_time()

        return False

    def add_box(self, timeout=4):
        scene = self.scene

        box_pose = geometry_msgs.msg.PoseStamped()
        box_pose.header.frame_id = "panda_leftfinger"
        box_pose.pose.orientation.w = 1.0
        box_pose.pose.position.z = 0.07  # slightly above the end effector
        box_name = "box"
        scene.add_box(box_name, box_pose, size=(0.1, 0.1, 0.1))

        self.box_name = box_name
        return self.wait_for_state_update(True, timeout=timeout)

    def attach_box(self, timeout=4):
        box_name = self.box_name
        robot = self.robot
        scene = self.scene
        eef_link = self.eef_link

        grasping_group = 'hand'  # panda srdf 中的groupname 是 hand
        touch_links = robot.get_link_names(group=grasping_group)

        # 将box 加到 eef_link
        scene.attach_box(eef_link, box_name, touch_links=touch_links)  # touch_links和box 之间的碰撞要忽略

        return self.wait_for_state_update(box_is_known=False, box_is_attached=True, timeout=timeout)

    def detach_box(self, timeout=4):
        box_name = self.box_name
        scene = self.scene
        eef_link = self.eef_link
        scene.remove_attached_object(eef_link, name=box_name)
        return self.wait_for_state_update(box_is_known=True, box_is_attached=False, timeout=timeout)

    """
    The object must be detached before we can remove it from the world
    """

    def remove_box(self, timeout=4):
        box_name = self.box_name
        scene = self.scene

        scene.remove_world_object(box_name)
        return self.wait_for_state_update(box_is_known=False, box_is_attached=False, timeout=timeout)


def main():
    try:
        print ""
        print "----------------------------------------------------------"
        print "Welcome to the MoveIt MoveGroup Python Interface Tutorial by zcb"
        print "----------------------------------------------------------"
        print "Press Ctrl-D to exit at any time"
        print ""

        print "============ Press `Enter` to begin the tutorial by setting up the moveit_commander ..."
        raw_input()
        tutorial = MyMoveGroupInterface()

        print "============ Press `Enter` to execute a movement using a joint state goal ..."
        raw_input()
        tutorial.go_to_joint_state()

        print "============ Press `Enter` to execute a movement using a pose goal ..."
        raw_input()
        tutorial.go_to_pose_goal()

        print "============ Press `Enter` to plan and display a Cartesian path"
        raw_input()
        cartesian_plan, fraction = tutorial.plan_cartesian_path()

        print "============ Press `Enter` to replay to display above Cartesian path"
        raw_input()
        tutorial.display_trajectory(cartesian_plan)

        print "============ Press `Enter` to execute above Cartesian path"
        raw_input()
        tutorial.execute_plan(cartesian_plan)

        print "============ Press `Enter` to add a box to the planning scene"
        raw_input()
        tutorial.add_box()

        print "============ Press `Enter` to attach a Box to the Panda robot"
        raw_input()
        tutorial.attach_box()

        print "============ Press `Enter` to execute above Cartesian path"
        raw_input()
        tutorial.execute_plan(cartesian_plan)

        print "============ Press `Enter` to detach the box from the Panda robot"
        raw_input()
        tutorial.detach_box()

        print "============ Press `Enter` to remove the box from the planning scene"
        raw_input()
        tutorial.remove_box()

        print "============ Demo complete!"

    except rospy.ROSInterruptException:
        return
    except KeyboardInterrupt:
        return


if __name__ == '__main__':
    main()
