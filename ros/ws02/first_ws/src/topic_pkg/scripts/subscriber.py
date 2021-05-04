#! /usr/bin/env python
# coding=utf8

import rospy
from std_msgs.msg import String


def callback(msg):
    if not isinstance(msg, String):
        return

    print msg.data


if __name__ == '__main__':
    nodeName = "subscriber_node"
    rospy.init_node(nodeName)

    topicName = "/zcb01/topic"
    rospy.Subscriber(topicName, String, callback=callback, queue_size=1000)

    rospy.spin()
