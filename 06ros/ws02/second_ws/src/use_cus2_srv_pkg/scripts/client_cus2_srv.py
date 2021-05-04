#! /usr/bin/env python
# coding=utf8

import rospy
from custom2_srvs.srv import GenStudentId, GenStudentIdRequest, GenStudentIdResponse

if __name__ == '__main__':
    nodeName = "client_node"
    rospy.init_node(nodeName)

    serviceName = "/zcb01/service"
    client = rospy.ServiceProxy(serviceName, GenStudentId)
    client.wait_for_service()

    request = GenStudentIdRequest()
    request.stu.name = "tom"
    request.stu.age = 18

    try:
        response = client.call(request)
        if isinstance(response, GenStudentIdResponse):
            rospy.loginfo("call success,result is %s" % response.id)
    except Exception as e:
        print e
        rospy.loginfo("call failed")
