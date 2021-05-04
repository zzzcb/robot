#! /usr/bin/env python
# coding:utf8

import rospy
from custom_msgs.msg import Student


def topic_callback(msg):
    if not isinstance(msg, Student):
        return
    print "%s %d" % (msg.name, msg.age)


if __name__ == '__main__':
    nodeName = "subscriber_node"
    rospy.init_node(nodeName)

    topicName = "/zcb01/topic"
    rospy.Subscriber(topicName, Student, topic_callback)

    rospy.spin()
