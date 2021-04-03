#! /usr/bin/env python
# coding:utf8
import sys
import rospy
from PyQt5.QtWidgets import (
    QWidget, QApplication, QFormLayout, QLineEdit, QPushButton,
)
from geometry_msgs.msg import Twist


def send_msg():
    global publisher, linearXEdit, angularZEdit
    msg = Twist()
    linearX = float(linearXEdit.text())
    angularZ = float(angularZEdit.text())
    msg.linear.x = linearX
    msg.angular.z = angularZ * 3.14 / 180
    publisher.publish(msg)


if __name__ == '__main__':
    # ros
    nodeName = "ctrl_turtle_py_node"
    rospy.init_node(nodeName)
    publisher = rospy.Publisher("/turtle1/cmd_vel", Twist, queue_size=1000)

    # qt
    app = QApplication(sys.argv)
    window = QWidget()
    window.setWindowTitle("小乌龟速度控制")
    layout = QFormLayout(window)

    linearXEdit = QLineEdit("0.0")
    angularZEdit = QLineEdit("0.0")
    layout.addRow("线速度", linearXEdit)
    layout.addRow("角速度", angularZEdit)

    sendBtn = QPushButton("发送")
    layout.addRow(sendBtn)

    # slot func
    sendBtn.clicked.connect(send_msg)

    window.show()

    sys.exit(app.exec_())
