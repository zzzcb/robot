#!/usr/bin/env python
# coding:utf8

import roslib;

roslib.load_manifest('ur_driver')
import rospy
from ur_msgs.srv import SetIO,SetIORequest,SetIOResponse

import time


def set_io(pin,state):
    serviceName = "/ur_driver/set_io"
    client = rospy.ServiceProxy(serviceName, SetIO)
    rospy.wait_for_service(serviceName)
    request = SetIORequest()
    request.fun = 1
    request.pin = pin
    request.state = state
    res = client.call(request)
    if res:
        print "Successfull D0 gripper IO states change."
    else:
        print "Failed to change D0 gripper IO states."
    return res 

if __name__ == '__main__':
    pass
    #set_io(0,1) # 开 
    #time.sleep(10)
    #set_io(0,0) # 关

