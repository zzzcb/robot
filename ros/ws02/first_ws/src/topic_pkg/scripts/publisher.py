#! /usr/bin/env python
# coding=utf8

import rospy
from std_msgs.msg import String

if __name__ == '__main__':
    nodeName = "publisher_node"
    rospy.init_node(nodeName)

    topicName = "/zcb01/topic"
    publisher = rospy.Publisher(topicName, String, queue_size=1000)

    msg = String()
    idx = 0
    rate = rospy.Rate(2)
    while not rospy.is_shutdown():
        msg.data = "hello " + str(idx)
        publisher.publish(msg)

        idx += 1
        rate.sleep()
