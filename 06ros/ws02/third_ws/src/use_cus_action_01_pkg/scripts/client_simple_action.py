#! /usr/bin/env python
# coding=utf8

import rospy
from actionlib import SimpleActionClient, GoalStatus
from custom_action_msgs.msg import (
    CountNumberAction, CountNumberGoal, CountNumberFeedback,
    CountNumberResult
)


def done_cb(state, result):
    # if not isinstance(state,GoalStatus):
    #    return

    # if not isinstance(result,CountNumberResult):
    #    return

    if state == GoalStatus.ABORTED:
        rospy.loginfo("server working error, don't finish my job.")
    elif state == GoalStatus.PREEMPTED:
        rospy.loginfo("client cancel job.")
    elif state == GoalStatus.SUCCEEDED:
        rospy.loginfo("server finish job.")
        rospy.loginfo("[done] result:%f" % result.result)


def active_cb():
    rospy.loginfo("[active]")


def feedback_cb(feedback):
    # if not isinstance((feedback,CountNumberFeedback)):
    #    return

    rospy.loginfo("[feedback] percent:%f %%" % (feedback.rate * 100))


if __name__ == '__main__':
    nodeName = "client_node"
    rospy.init_node(nodeName)

    actionName = "/zcb01/action"
    client = SimpleActionClient(actionName, CountNumberAction)
    client.wait_for_server()

    goal = CountNumberGoal()
    goal.max = 101
    goal.duration = 0.1
    client.send_goal(goal, done_cb, active_cb, feedback_cb)

    # d = rospy.Duration(3)
    # rospy.sleep(d)
    # client.cancel_goal()

    rospy.spin()
