#! /usr/bin/env python
# coding:utf8

import rospy

if __name__ == '__main__':
    nodeName = "hellopy_node"
    rospy.init_node(nodeName)

    idx = 0
    rate = rospy.Rate(5)  # hz
    while not rospy.is_shutdown():
        print "hellopkg's py %d" % idx
        idx += 1
        rate.sleep()

    rospy.spin()
