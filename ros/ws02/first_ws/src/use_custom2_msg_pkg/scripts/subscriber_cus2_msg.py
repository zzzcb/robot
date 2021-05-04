#! /usr/bin/env python
# coding:utf8

import rospy
from custom2_msgs.msg import Team


def topic_callback(msg):
    if not isinstance(msg, Team):
        return
    print "%s %s %d" % (msg.name, msg.leader.name, msg.leader.age)


if __name__ == '__main__':
    nodeName = "subscriber_node"
    rospy.init_node(nodeName)

    topicName = "/zcb01/topic"
    rospy.Subscriber(topicName, Team, topic_callback)

    rospy.spin()
