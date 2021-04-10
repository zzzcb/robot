#! /usr/bin/env python
# coding:utf8
from PyQt5.QtWidgets import (
    QWidget, QFormLayout, QPushButton,
    QCheckBox, QLineEdit, QHBoxLayout,
)
from PyQt5.QtCore import (
    QTimer
)
import rospy
# srv
from std_srvs.srv import Empty, EmptyRequest
from turtlesim.srv import (
    Spawn, SpawnRequest, Kill, KillRequest,
    SetPen, SetPenRequest,
    TeleportAbsolute, TeleportAbsoluteRequest,
    TeleportRelative, TeleportRelativeRequest,
)


class MainWindow(QWidget):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.setWindowTitle("小乌龟控制")
        self.setFixedSize(500, 300)

        # QTimer
        self.timer = QTimer()
        self.timer.setInterval(16)  # 1000 /60fps = 16
        self.timer.timeout.connect(self.onUpdate)
        self.timer.start()

        # ui
        self.setUI()

        # connect to slot
        self.connectSlot()

    def setUI(self):
        self.ly = QFormLayout(self)

        self.clearBtn = QPushButton("清理画布")
        self.ly.addRow(self.clearBtn)

        self.resetBtn = QPushButton("重置")
        self.ly.addRow(self.resetBtn)

        h_ly_spawn = QHBoxLayout()
        self.spawnX = QLineEdit()
        self.spawnX.setPlaceholderText("X坐标")
        self.spawnY = QLineEdit()
        self.spawnY.setPlaceholderText("Y坐标")
        self.spawnTheta = QLineEdit()
        self.spawnTheta.setPlaceholderText("角度")
        self.spawnName = QLineEdit()
        self.spawnName.setPlaceholderText("名字")
        self.spawnBtn = QPushButton("创建小乌龟")
        h_ly_spawn.addWidget(self.spawnX)
        h_ly_spawn.addWidget(self.spawnY)
        h_ly_spawn.addWidget(self.spawnTheta)
        h_ly_spawn.addWidget(self.spawnName)
        h_ly_spawn.addWidget(self.spawnBtn)
        self.ly.addRow(h_ly_spawn)

        h_ly_kill = QHBoxLayout()
        self.killName = QLineEdit()
        self.killName.setPlaceholderText("名字")
        self.killBtn = QPushButton("杀死小乌龟")
        h_ly_kill.addWidget(self.killName)
        h_ly_kill.addWidget(self.killBtn)
        self.ly.addRow(h_ly_kill)

        h_ly_set_pen = QHBoxLayout()
        self.setPenName = QLineEdit()
        self.setPenName.setPlaceholderText("名字")
        self.setPenR = QLineEdit()
        self.setPenR.setPlaceholderText("红")
        self.setPenG = QLineEdit()
        self.setPenG.setPlaceholderText("绿")
        self.setPenB = QLineEdit()
        self.setPenB.setPlaceholderText("蓝")
        self.setPenWidth = QLineEdit()
        self.setPenWidth.setPlaceholderText("粗细")
        self.setPenOff = QCheckBox("关闭")
        self.setPenBtn = QPushButton("设置画笔")
        h_ly_set_pen.addWidget(self.setPenName)
        h_ly_set_pen.addWidget(self.setPenR)
        h_ly_set_pen.addWidget(self.setPenG)
        h_ly_set_pen.addWidget(self.setPenB)
        h_ly_set_pen.addWidget(self.setPenWidth)
        h_ly_set_pen.addWidget(self.setPenOff)
        h_ly_set_pen.addWidget(self.setPenBtn)
        self.ly.addRow(h_ly_set_pen)

        h_ly_abs = QHBoxLayout()
        self.abs_name = QLineEdit()
        self.abs_name.setPlaceholderText("名字")
        self.abs_x = QLineEdit()
        self.abs_x.setPlaceholderText("X坐标")
        self.abs_y = QLineEdit()
        self.abs_y.setPlaceholderText("Y坐标")
        self.abs_theta = QLineEdit()
        self.abs_theta.setPlaceholderText("角度")
        self.teleportAbsoluteBtn = QPushButton("设置绝对位置")
        h_ly_abs.addWidget(self.abs_name)
        h_ly_abs.addWidget(self.abs_x)
        h_ly_abs.addWidget(self.abs_y)
        h_ly_abs.addWidget(self.abs_theta)
        h_ly_abs.addWidget(self.teleportAbsoluteBtn)
        self.ly.addRow(h_ly_abs)

        h_ly_rel = QHBoxLayout()
        self.rel_name = QLineEdit()
        self.rel_name.setPlaceholderText("名字")
        self.rel_linear = QLineEdit()
        self.rel_linear.setPlaceholderText("线速度")
        self.rel_angular = QLineEdit()
        self.rel_angular.setPlaceholderText("角速度")
        self.teleportRelativeBtn = QPushButton("设置相对位置")
        h_ly_rel.addWidget(self.rel_name)
        h_ly_rel.addWidget(self.rel_linear)
        h_ly_rel.addWidget(self.rel_angular)
        h_ly_rel.addWidget(self.teleportRelativeBtn)
        self.ly.addRow(h_ly_rel)

    def onUpdate(self):
        # qt 回调
        self.update()

        if rospy.is_shutdown():
            self.close()

    def connectSlot(self):
        self.clearBtn.clicked.connect(self.clickClear)
        self.resetBtn.clicked.connect(self.clickReset)
        self.spawnBtn.clicked.connect(self.clickSpawn)
        self.killBtn.clicked.connect(self.clickKill)
        self.setPenBtn.clicked.connect(self.clickSetPen)
        self.teleportAbsoluteBtn.clicked.connect(self.clickAbs)
        self.teleportRelativeBtn.clicked.connect(self.clickRel)

    def clickClear(self):
        clear_client = rospy.ServiceProxy("/clear", Empty)
        request = EmptyRequest()
        clear_client.call(request)
        clear_client.close()  # 关闭临时的 client

    def clickReset(self):
        reset_client = rospy.ServiceProxy("/reset", Empty)
        request = EmptyRequest()
        reset_client.call(request)
        reset_client.close()

    def clickSpawn(self):
        spawn_client = rospy.ServiceProxy("/spawn", Spawn)
        request = SpawnRequest()

        request.x = float(self.spawnX.text())
        request.y = float(self.spawnY.text())
        request.theta = float(self.spawnTheta.text()) * 3.14 / 180
        request.name = self.spawnName.text()

        spawn_client.call(request)
        spawn_client.close()

    def clickKill(self):
        kill_client = rospy.ServiceProxy("/kill", Kill)
        request = KillRequest()

        request.name = self.killName.text()

        kill_client.call(request)
        kill_client.close()

    def clickSetPen(self):
        set_pen_client = rospy.ServiceProxy("/" + self.setPenName.text() +
                                            "/set_pen", SetPen)
        request = SetPenRequest()

        request.r = float(self.setPenR.text())
        request.g = float(self.setPenG.text())
        request.b = float(self.setPenB.text())
        request.width = float(self.setPenWidth.text())
        request.off = float(self.setPenOff.isChecked())

        set_pen_client.call(request)
        set_pen_client.close()

    def clickAbs(self):
        abs_client = rospy.ServiceProxy("/" + self.abs_name.text() +
                                        "/teleport_absolute", TeleportAbsolute)
        request = TeleportAbsoluteRequest()

        request.x = float(self.abs_x.text())
        request.y = float(self.abs_y.text())
        request.theta = float(self.abs_theta.text()) * 3.14 / 180

        abs_client.call(request)
        abs_client.close()

    def clickRel(self):
        rel_client = rospy.ServiceProxy("/" + self.rel_name.text() +
                                        "/teleport_relative", TeleportRelative)
        request = TeleportRelativeRequest()
        request.linear = float(self.rel_linear.text())
        request.angular = float(self.rel_angular.text()) * 3.14 / 180

        rel_client.call(request)
        rel_client.close()
