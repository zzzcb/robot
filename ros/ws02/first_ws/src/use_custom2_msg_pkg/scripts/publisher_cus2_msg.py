#! /usr/bin/env python
# coding:utf8

import rospy
from custom2_msgs.msg import Team
from custom_msgs.msg import Student

if __name__ == '__main__':

    nodeName = "publisher_node"
    rospy.init_node(nodeName)

    topicName = "/zcb01/topic"
    pub = rospy.Publisher(topicName, Team, queue_size=1000)

    rate = rospy.Rate(2)
    msg = Team()
    stu = Student()
    idx = 0
    while not rospy.is_shutdown():
        msg.name = "NCHU%d" % idx
        stu.name = "tom%d" % idx
        stu.age = idx
        msg.leader = stu
        pub.publish(msg)

        idx += 1
        rate.sleep()
