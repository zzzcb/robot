#! /usr/bin/env python
# coding:utf8

import rospy
from std_msgs.msg import String


def topic_callback(data):
    print data


if __name__ == '__main__':
    nodeName = "topic_python_node"
    rospy.init_node(nodeName)

    topicName = "/python/topic"
    rospy.Subscriber(topicName, String, topic_callback)

    rospy.spin()
