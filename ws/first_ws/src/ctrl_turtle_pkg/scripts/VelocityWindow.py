#! /usr/bin/env python
# coding:utf-8
from PyQt5.QtWidgets import (
    QWidget, QFormLayout, QLineEdit, QPushButton,
)
import rospy
from geometry_msgs.msg import Twist


class VelocityWindow(QWidget):
    def __init__(self, publisher):
        super(VelocityWindow, self).__init__()
        self.publisher = publisher
        self.setWindowTitle("小乌龟速度控制")

        self.layout = QFormLayout(self)
        self.linearXEdit = QLineEdit("0.0")
        self.angularZEdit = QLineEdit("0.0")
        self.layout.addRow("线速度", self.linearXEdit)
        self.layout.addRow("角速度", self.angularZEdit)

        self.sendBtn = QPushButton("发送")
        self.layout.addRow(self.sendBtn)

        # slot func
        self.sendBtn.clicked.connect(self.send_msg)

    def send_msg(self):
        if not isinstance(self.publisher, rospy.Publisher):
            return
        msg = Twist()
        linearX = float(self.linearXEdit.text())
        angularZ = float(self.angularZEdit.text())

        msg.linear.x = linearX
        msg.angular.z = angularZ * 3.14 / 180

        self.publisher.publish(msg)