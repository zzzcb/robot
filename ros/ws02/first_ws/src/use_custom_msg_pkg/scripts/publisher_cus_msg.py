#! /usr/bin/env python
# coding:utf8

import rospy
from custom_msgs.msg import Student

if __name__ == '__main__':

    nodeName = "publisher_node"
    rospy.init_node(nodeName)

    topicName = "/zcb01/topic"
    pub = rospy.Publisher(topicName, Student, queue_size=1000)

    rate = rospy.Rate(2)
    msg = Student()
    idx = 0
    while not rospy.is_shutdown():
        msg.name = "tom%d" % idx
        msg.age = idx
        pub.publish(msg)

        idx += 1
        rate.sleep()


