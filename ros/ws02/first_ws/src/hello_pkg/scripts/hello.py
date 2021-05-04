#! /usr/bin/env python
# coding=utf8

import rospy

if __name__ == '__main__':
    nodeName = "hello_node"
    rospy.init_node(nodeName)

    rate = rospy.Rate(2)
    while not rospy.is_shutdown():
        print "hello ros"
        rate.sleep()

    rospy.spin()
