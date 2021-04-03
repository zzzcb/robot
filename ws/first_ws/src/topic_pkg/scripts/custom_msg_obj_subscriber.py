#! /usr/bin/env python
# coding:utf8

import rospy
from demo_msgs.msg import Student, Team


def topic_callback(msg):
    if not isinstance(msg, Team):
        return
    print "==="
    print "team::name %s" % msg.name
    print "team::leader::name %s" % msg.leader.name
    print "team::leader::age %d" % msg.leader.age


if __name__ == '__main__':
    nodeName = "subscribe_custom_msg_py_node"
    rospy.init_node(nodeName)

    topicName = "/custom/msg/obj/topic"
    rospy.Subscriber(topicName, Team, topic_callback)

    rospy.spin()
