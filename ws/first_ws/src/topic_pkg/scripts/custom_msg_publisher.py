#! /usr/bin/env python
# coding:utf8

import rospy
from demo_msgs.msg import Student

if __name__ == '__main__':
    nodeName = "publish_custom_msg_py_node"
    rospy.init_node(nodeName)

    topicName = "/custom/msg/topic"
    pub = rospy.Publisher(topicName, Student, queue_size=1000)

    rate = rospy.Rate(1)
    stu = Student()
    idx = 0
    while not rospy.is_shutdown():
        stu.name = "tom %d" % idx
        stu.age = idx
        pub.publish(stu)
        idx += 1
        rate.sleep()

    rospy.spin()
