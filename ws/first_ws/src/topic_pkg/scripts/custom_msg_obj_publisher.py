#! /usr/bin/env python
# coding:utf8

import rospy
from demo_msgs.msg import Student, Team

if __name__ == '__main__':
    nodeName = "publish_custom_msg_obj_py_node"
    rospy.init_node(nodeName)

    topicName = "/custom/msg/obj/topic"
    pub = rospy.Publisher(topicName, Team, queue_size=1000)

    rate = rospy.Rate(1)
    team = Team()
    stu = Student()

    idx = 0
    while not rospy.is_shutdown():
        team.name = "NCHU %d" % idx

        stu.name = "tom %d" % idx
        stu.age = idx
        team.leader = stu

        pub.publish(team)

        idx += 1
        rate.sleep()

    rospy.spin()
