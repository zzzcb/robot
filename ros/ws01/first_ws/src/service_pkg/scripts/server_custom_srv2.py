#! /usr/bin/env python
# coding:utf8

import rospy
from demo_srvs.srv import GetStudentId, GetStudentIdRequest, GetStudentIdResponse


def client_callback(request):
    if not isinstance(request, GetStudentIdRequest):
        return

    response = GetStudentIdResponse()
    name = request.stu.name
    age = request.stu.age
    response.id = name + str(age)

    return response


if __name__ == '__main__':
    nodeName = "python_service_node"
    rospy.init_node(nodeName)

    serviceName = "/python/service"

    # 与c++ api 不一致，
    server = rospy.Service(serviceName, GetStudentId, client_callback)

    rospy.spin()
