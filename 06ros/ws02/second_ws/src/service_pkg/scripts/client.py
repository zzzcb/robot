#! /usr/bin/env python
# coding=utf8

import rospy
from rospy_tutorials.srv import AddTwoInts, AddTwoIntsRequest, AddTwoIntsResponse

if __name__ == '__main__':
    nodeName = "client_node"
    rospy.init_node(nodeName)

    serviceName = "/zcb01/service"
    client = rospy.ServiceProxy(serviceName, AddTwoInts)
    client.wait_for_service()

    request = AddTwoIntsRequest()
    request.a = 10
    request.b = 20
    try:
        response = client.call(request)
        if isinstance(response, AddTwoIntsResponse):
            rospy.loginfo("call success,result is %d" % response.sum)
    except:
        rospy.loginfo("call failed")
