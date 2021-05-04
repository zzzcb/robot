#! /usr/bin/env python
# coding:utf8

import rospy
from custom4_msgs.msg import Team
from custom_msgs.msg import Student

if __name__ == '__main__':

    nodeName = "publisher_node"
    rospy.init_node(nodeName)

    topicName = "/zcb01/topic"
    pub = rospy.Publisher(topicName, Team, queue_size=1000)

    rate = rospy.Rate(2)
    msg = Team()
    leader = Student()

    mem1 = Student()
    mem2 = Student()
    mem3 = Student()

    idx = 0
    while not rospy.is_shutdown():
        msg.name = "NCHU%d" % idx
        leader.name = "tom%d" % idx
        leader.age = idx
        msg.leader = leader
        msg.intro.data = "NIU bi 战队"

        msg.members = []
        mem1.name = "成员01";mem1.age = idx;msg.members.append(mem1)
        mem2.name = "成员02";mem2.age = idx + 1;msg.members.append(mem2)
        mem3.name = "成员03";mem3.age = idx + 2;msg.members.append(mem3)

        pub.publish(msg)

        idx += 1
        rate.sleep()
