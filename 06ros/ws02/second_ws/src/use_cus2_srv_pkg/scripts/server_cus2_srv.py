#! /usr/bin/env python
# coding=utf8

import rospy
from custom2_srvs.srv import GenStudentId, GenStudentIdRequest, GenStudentIdResponse


def callback(request):
    if not isinstance(request, GenStudentIdRequest):
        return
    response = GenStudentIdResponse()

    response.id = "000 %s 111 %d 000" % (request.stu.name, request.stu.age)

    return response


if __name__ == '__main__':
    nodeName = "server_node"
    rospy.init_node(nodeName)

    serviceName = "/zcb01/service"
    server = rospy.Service(serviceName, GenStudentId, callback)  # server

    rospy.spin()
