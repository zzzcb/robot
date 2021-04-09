#! /usr/bin/env python
# coding:utf8
from PyQt5.QtWidgets import (
    QWidget, QFormLayout, QLineEdit, QPushButton,
    QLabel,
)
from PyQt5.QtCore import (
    QTimer,
)
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist
import rospy


class VelocityWindow02(QWidget):
    def __init__(self, publisher, sub_topic_name):
        super(VelocityWindow02, self).__init__()

        self.publisher = publisher
        sub = rospy.Subscriber(sub_topic_name, Pose, self.update_pose, queue_size=1000)
        self.timer = QTimer(self)
        self.timer.setInterval(16)
        self.timer.start()
        self.timer.timeout.connect(self.onUpdate)

        self.setWindowTitle("小乌龟控制器")
        self.linearX = QLineEdit("0.0")
        self.angularZ = QLineEdit("0.0")
        self.pos_x_label = QLabel("0.0")
        self.pos_y_label = QLabel("0.0")
        self.linear_x_label = QLabel("0.0")
        self.angular_z_label = QLabel("0.0")
        self.theta_label = QLabel("0.0")
        self.sendBtn = QPushButton("发送", self)

        self.ly = QFormLayout(self)
        self.ly.addRow("线速度", self.linearX)
        self.ly.addRow("角速度", self.angularZ)
        self.ly.addRow("当前x坐标", self.pos_x_label)
        self.ly.addRow("当前y坐标", self.pos_y_label)
        self.ly.addRow("当前线速度", self.linear_x_label)
        self.ly.addRow("当前角速度", self.angular_z_label)
        self.ly.addRow("当前角度", self.theta_label)
        self.ly.addRow(self.sendBtn)

        self.sendBtn.clicked.connect(self.send_msg)

    def send_msg(self):
        if not isinstance(self.publisher, rospy.Publisher):
            return

        linearX = float(self.linearX.text())
        angularZ = float(self.angularZ.text()) * 3.14 / 180
        twist = Twist()
        twist.linear.x = linearX
        twist.angular.z = angularZ

        self.publisher.publish(twist)

    def update_pose(self, msg):
        if not isinstance(msg, Pose):
            return
        self.pos_x_label.setText(str(msg.x))
        self.pos_y_label.setText(str(msg.y))
        self.linear_x_label.setText(str(msg.linear_velocity))
        self.angular_z_label.setText(str(msg.angular_velocity * 180 / 3.14))
        self.theta_label.setText(str(msg.theta * 180 / 3.14))

    def onUpdate(self):  # 手动刷新
        self.update()  # QT 渲染
        if rospy.is_shutdown():
            self.close()


