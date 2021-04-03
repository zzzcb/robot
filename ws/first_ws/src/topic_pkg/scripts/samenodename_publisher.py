#! /usr/bin/env python
# coding:utf8

import rospy
from std_msgs.msg import String

if __name__ == '__main__':

    nodeName = "topic_py_node"
    # rospy.init_node(nodeName)
    rospy.init_node(nodeName, anonymous=True)

    topicName = "/python/topic"
    pub = rospy.Publisher(topicName, String, queue_size=1000)

    # msg = String()
    # idx = 0
    # rate = rospy.Rate(1)
    # while not rospy.is_shutdown():
    #    msg.data = "hello %d" % idx
    #    pub.publish(msg)
    #    idx += 1
    #    rate.sleep()

    idx = 0
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        pub.publish(String("hello 你好%d" % idx))
        idx += 1
        rate.sleep()

    rospy.spin()
