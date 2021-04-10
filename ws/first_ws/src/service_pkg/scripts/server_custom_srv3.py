#! /usr/bin/env python
# coding:utf8

import rospy
from demo_srvs.srv import FindTeam, FindTeamRequest, FindTeamResponse


def client_callback(request):
    if not isinstance(request, FindTeamRequest):
        return

    response = FindTeamResponse()
    name = request.stu.name
    age = request.stu.age
    response.team.name = "NCHU"
    response.team.leader.name = name
    response.team.leader.age = age

    return response


if __name__ == '__main__':
    nodeName = "python_service_node"
    rospy.init_node(nodeName)

    serviceName = "/python/service"

    # 与c++ api 不一致，
    server = rospy.Service(serviceName, FindTeam, client_callback)

    rospy.spin()
