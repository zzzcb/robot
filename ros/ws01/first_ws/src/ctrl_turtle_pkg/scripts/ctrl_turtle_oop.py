#! /usr/bin/env python
# coding:utf8

import rospy
import sys
from PyQt5.QtWidgets import (
    QApplication,
)
from VelocityWindow import VelocityWindow
from geometry_msgs.msg import Twist


if __name__ == '__main__':
    # ros
    nodeName = "ctrl_turtle_py_node"
    rospy.init_node(nodeName)
    publisher = rospy.Publisher("/turtle1/cmd_vel", Twist, queue_size=1000)

    # qt
    app = QApplication(sys.argv)
    window = VelocityWindow(publisher)
    window.show()

    sys.exit(app.exec_())
