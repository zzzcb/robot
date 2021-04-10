#! /usr/bin/env python
# coding:utf8

import rospy
from PyQt5.QtWidgets import (
    QApplication,
)
import sys
from MainWindow import MainWindow

if __name__ == '__main__':
    # ros
    nodeName = "python_client_node"  # python_client_node
    rospy.init_node(nodeName)

    # qt
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
