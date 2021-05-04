#! /usr/bin/env python
# coding=utf8

import rospy
from rospy_tutorials.srv import AddTwoInts, AddTwoIntsRequest, AddTwoIntsResponse


def callback(request):
    if not isinstance(request, AddTwoIntsRequest):
        return
    a = request.a
    b = request.b

    response = AddTwoIntsResponse()
    response.sum = a + b

    return response


if __name__ == '__main__':
    nodeName = "server_node"
    rospy.init_node(nodeName)

    serviceName = "/zcb01/service"
    server = rospy.Service(serviceName, AddTwoInts, callback)  # server

    rospy.spin()
