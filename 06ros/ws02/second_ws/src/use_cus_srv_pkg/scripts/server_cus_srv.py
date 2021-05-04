#! /usr/bin/env python
# coding=utf8

import rospy
from custom_srvs.srv import NumOption, NumOptionRequest, NumOptionResponse


def callback(request):
    if not isinstance(request, NumOptionRequest):
        return
    a = request.a
    b = request.b
    op = request.op

    response = NumOptionResponse()
    if op == "+":
        response.res = a + b
    elif op == "-":
        response.res = a - b
    elif op == "*":
        response.res = a * b
    elif op == "/":
        response.res = a / b
    elif op == "%":
        response.res = a % b

    return response


if __name__ == '__main__':
    nodeName = "server_node"
    rospy.init_node(nodeName)

    serviceName = "/zcb01/service"
    server = rospy.Service(serviceName, NumOption, callback)  # server

    rospy.spin()
