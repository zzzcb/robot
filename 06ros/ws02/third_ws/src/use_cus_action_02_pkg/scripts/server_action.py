#! /usr/bin/env python
# coding=utf8

import rospy
from actionlib import ActionServer, ServerGoalHandle
from custom_action_msgs.msg import (
    CountNumberAction, CountNumberGoal, CountNumberFeedback,
    CountNumberResult
)
import threading

isCancel = False

# isAborted = False


def do_goal(handle):
    global isCancel, isAborted
    if not isinstance(handle, ServerGoalHandle):
        return

    goal = handle.get_goal()
    if not isinstance(goal, CountNumberGoal):
        return
    max = goal.max
    duration = goal.duration

    result = CountNumberResult()

    if max < 0 or max > 100:
        handle.set_rejected(result, " max should in (0,100] [zcb]")
        return
    else:
        handle.set_accepted()

    cnt = 0  # 从0开始数数, 数到max
    dur = rospy.Duration(duration)
    while not rospy.is_shutdown() and cnt < max:
        # 3 检测client 是否取消
        if isCancel:
            break
        # 4server自己崩了
        # if cnt > 20:
        #     isAborted = True
        #     break
        cnt += 1
        rospy.loginfo(cnt)

        # 1.反馈进度
        feedback = CountNumberFeedback()
        feedback.rate = cnt / (max * 1.0)
        handle.publish_feedback(feedback)

        rospy.sleep(dur)

    # 2.反馈结果
    result.result = cnt
    if isCancel:
        handle.set_canceled(result, " client cancel[zcb]")
        isCancel = False
    # elif isAborted:
    #     handle.set_aborted(result," server aborted[zcb]")
    #     isAborted = False
    else:
        handle.set_succeeded(result, " success [zcb]")


def goal_cb(handle):
    t = threading.Thread(target=do_goal, args=(handle,))
    t.start()


def cancel_cb(handle):
    global isCancel
    rospy.loginfo("cancel cb")
    isCancel = True


if __name__ == '__main__':
    nodeName = "server_node"
    rospy.init_node(nodeName)

    actionName = "/zcb01/action"
    server = ActionServer(actionName, CountNumberAction, goal_cb, cancel_cb, False)
    server.start()

    rospy.spin()
