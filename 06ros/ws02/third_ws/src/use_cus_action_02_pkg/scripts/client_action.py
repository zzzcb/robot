#! /usr/bin/env python
# coding=utf8

import rospy
from actionlib import ActionClient, ClientGoalHandle, CommState, TerminalState
from custom_action_msgs.msg import (
    CountNumberAction, CountNumberGoal, CountNumberFeedback,
    CountNumberResult
)


def transition_cb(handle):
    if not isinstance(handle, ClientGoalHandle):
        return
    state = handle.get_comm_state()
    if state == CommState.ACTIVE:
        rospy.loginfo("ACTIVE")
    elif state == CommState.DONE:
        terminal_state = handle.get_terminal_state()
        text = handle.get_goal_status_text()
        if terminal_state == TerminalState.SUCCEEDED:
            rospy.loginfo("SUCCEEDED %s" % text)
        elif terminal_state == TerminalState.ABORTED:
            rospy.loginfo("ABORTED %s" % text)
        elif terminal_state == TerminalState.PREEMPTED:
            rospy.loginfo("PREEMPTED %s" % text)
        elif terminal_state == TerminalState.REJECTED:
            rospy.loginfo("REJECTED %s" % text)
        elif terminal_state == TerminalState.RECALLED:
            rospy.loginfo("RECALLED %s" % text)
    else:
        rospy.loginfo("RECALLED %s" % state)  # 其他


def feedback_cb(handle, feedback):
    if not isinstance(feedback, CountNumberFeedback):
        return
    rospy.loginfo("feedback_cb %f %%" % (feedback.rate * 100))


if __name__ == '__main__':
    nodeName = "client_node"
    rospy.init_node(nodeName, anonymous=True)

    actionName = "/zcb01/action"
    client = ActionClient(actionName, CountNumberAction)
    client.wait_for_server()

    goal = CountNumberGoal()
    goal.max = 88
    goal.duration = 0.1

    # 这里一定要接受返回值
    handle = client.send_goal(goal, transition_cb, feedback_cb)

    # d = rospy.Duration(3)
    # rospy.sleep(d)
    # handle.cancel()

    rospy.spin()
