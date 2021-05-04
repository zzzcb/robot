#! /usr/bin/env python
# coding:utf8

import rospy
from demo_srvs.srv import NumOption, NumOptionRequest, NumOptionResponse


def client_callback(request):
    if not isinstance(request, NumOptionRequest):
        return

    response = NumOptionResponse()
    option = request.option

    if option == "+":
        response.result = request.a + request.b
    elif option == "-":
        response.result = request.a - request.b
    elif option == "*":
        response.result = request.a * request.b
    elif option == "/":
        response.result = request.a / request.b
    elif option == "%":
        response.result = request.a % request.b
    else:
        return None

    return response


if __name__ == '__main__':
    nodeName = "python_service_node"
    rospy.init_node(nodeName)

    serviceName = "/python/service"

    # 与c++ api 不一致，
    server = rospy.Service(serviceName, NumOption, client_callback)

    rospy.spin()
