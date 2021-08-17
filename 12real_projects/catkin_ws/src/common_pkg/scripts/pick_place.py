#!/usr/bin/env python
# coding:utf8

import time
import sys
import roslib;

roslib.load_manifest('ur_driver')
import rospy
import actionlib
from control_msgs.msg import FollowJointTrajectoryAction, FollowJointTrajectoryGoal
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from sensor_msgs.msg import JointState
from math import pi

from control_xipan import set_io

JOINT_NAMES = ['shoulder_pan_joint', 'shoulder_lift_joint', 'elbow_joint',
               'wrist_1_joint', 'wrist_2_joint', 'wrist_3_joint']
r = pi/180
Q1 = [-56.35*r, -121.88*r, -109.91*r, -35.54*r, 85.4*r, -0.12*r] # 抓取点
Q2 = [-56.35*r, -113.13*r, -106.96*r, -47.23*r, 85.37*r, -0.09*r]# 抓取后 起来一点
Q3 = [-3.88*r, -110.93*r, -45.66*r, -110.86*r, 85.23*r, 1.82*r]  # 放置点

client = None


def move1():
    goal = FollowJointTrajectoryGoal()
    goal.trajectory = JointTrajectory()
    goal.trajectory.joint_names = JOINT_NAMES
    try:
        joint_states = rospy.wait_for_message("joint_states", JointState)
        joints_pos = joint_states.position
        goal.trajectory.points = [
            JointTrajectoryPoint(positions=joints_pos, velocities=[0] * 6, time_from_start=rospy.Duration(0.0)),
            JointTrajectoryPoint(positions=Q1, velocities=[0] * 6, time_from_start=rospy.Duration(3.0)),
        ]
        client.send_goal(goal)
        client.wait_for_result()
        set_io(0,1)  # 吸气
        time.sleep(1)

        joint_states = rospy.wait_for_message("joint_states", JointState)
        joints_pos = joint_states.position
        goal.trajectory.points = [
            JointTrajectoryPoint(positions=joints_pos, velocities=[0] * 6, time_from_start=rospy.Duration(0.0)),
            JointTrajectoryPoint(positions=Q2, velocities=[0] * 6, time_from_start=rospy.Duration(3.0)),
            JointTrajectoryPoint(positions=Q3, velocities=[0] * 6, time_from_start=rospy.Duration(6.0)),
        ]
        client.send_goal(goal)
        client.wait_for_result()
        set_io(3,1)  # 吹气
        time.sleep(1)
        set_io(0,0) # 关闭io
        set_io(3,0)
 
    except KeyboardInterrupt:
        client.cancel_goal()
        raise
    except:
        raise


def main():
    global client
    try:
        rospy.init_node("test_move", anonymous=True, disable_signals=True)
        client = actionlib.SimpleActionClient('follow_joint_trajectory', FollowJointTrajectoryAction)
        print "Waiting for server..."
        client.wait_for_server()
        print "Connected to server"
        parameters = rospy.get_param(None)  # None 会获取到所有的 param
        index = str(parameters).find('prefix')
        if index > 0:
            prefix = str(parameters)[index + len("prefix': '"):(
                    index + len("prefix': '") + str(parameters)[index + len("prefix': '"):-1].find("'"))]
            for i, name in enumerate(JOINT_NAMES):
                JOINT_NAMES[i] = prefix + name

        print "This program makes the robot move between the following three poses:"
        print str([Q1[i]/r for i in xrange(0, 6)])
        print str([Q2[i]/r for i in xrange(0, 6)])

        print "Please make sure that your robot can move freely between these poses before proceeding!"
        inp = raw_input("Continue? y/n: ")[0]
        if inp == 'y':
            move1()
        else:
            print "Halting program"
    except KeyboardInterrupt:
        rospy.signal_shutdown("KeyboardInterrupt")
        raise


if __name__ == '__main__':
    main()

