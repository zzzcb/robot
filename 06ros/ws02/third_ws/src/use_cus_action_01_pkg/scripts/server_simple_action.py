#! /usr/bin/env python
# coding=utf8

import rospy
from actionlib import SimpleActionServer
from custom_action_msgs.msg import (
    CountNumberAction, CountNumberGoal, CountNumberFeedback,
    CountNumberResult
)

server = None


def callback(goal):
    # 1.实时将进度反馈给client
    # 2.如果执行完毕反馈给client
    # 3.如果client取消，就结束执行
    # 4.server 自己能力有限，干不完，自己abort
    if not isinstance(goal, CountNumberGoal):
        return
    max = goal.max
    dur = goal.duration

    cnt = 0
    duration = rospy.Duration(dur)
    isCancel = False
    # isAborted = False
    while not rospy.is_shutdown() and cnt < max:
        # 3 client 取消
        if server.is_preempt_requested():
            isCancel = True
            break
        # if cnt > 20:
        #     isAborted = True
        #     break

        cnt += 1
        rospy.loginfo(cnt)
        # 1 进度反馈
        feedback = CountNumberFeedback()
        feedback.rate = cnt * 1.0 / max
        server.publish_feedback(feedback)

        rospy.sleep(duration)

    # 2 结果返回
    result = CountNumberResult()
    result.result = cnt
    if isCancel:
        server.set_preempted(result)
        isCancel = False
    # elif isAborted:
    #     server.set_aborted(result)
    #     isAborted = False
    else:
        server.set_succeeded(result)


if __name__ == '__main__':
    nodeName = "server_node"
    rospy.init_node(nodeName)

    actionName = "/zcb01/action"
    server = SimpleActionServer(actionName, CountNumberAction, callback, False)
    server.start()

    rospy.spin()
