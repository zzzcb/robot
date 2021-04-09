#! /usr/bin/env python
# coding:utf8

import rospy
from geometry_msgs.msg import Twist


from PyQt5.QtWidgets import (
    QApplication
)

import sys
from VelocityWindow02 import VelocityWindow02

if __name__ == '__main__':
    # 1 ros
    nodeName = "ctrl_turtle_py_node"
    rospy.init_node(nodeName)

    pub_topic_name = "/turtle1/cmd_vel"
    pub = rospy.Publisher(pub_topic_name, Twist, queue_size=1000)

    sub_topic_name = "/turtle1/pose"

    # 2 qt
    app = QApplication(sys.argv)

    window = VelocityWindow02(pub, sub_topic_name)
    window.show()

    sys.exit(app.exec_())
