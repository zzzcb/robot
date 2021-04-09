#! /usr/bin/env python
# coding:utf8

import rospy
from rospy_tutorials.srv import AddTwoInts, AddTwoIntsRequest, AddTwoIntsResponse


def client_callback(request):
    if not isinstance(request, AddTwoIntsRequest):
        return

    response = AddTwoIntsResponse()
    response.sum = request.a + request.b

    return response


if __name__ == '__main__':
    nodeName = "python_service_node"
    rospy.init_node(nodeName)

    serviceName = "/python/service"

    # 与c++ api 不一致，
    server = rospy.Service(serviceName, AddTwoInts, client_callback)

    rospy.spin()
