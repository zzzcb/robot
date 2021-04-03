#! /usr/bin/env python
# coding:utf8

import rospy
from demo_msgs.msg import Student


def topic_callback(msg):
    if not isinstance(msg, Student):
        return
    print "name:%s" % msg.name
    print "age:%d" % msg.age


if __name__ == '__main__':
    nodeName = "subscribe_custom_msg_py_node"
    rospy.init_node(nodeName)

    topicName = "/custom/msg/topic"
    rospy.Subscriber(topicName, Student, topic_callback)

    rospy.spin()
