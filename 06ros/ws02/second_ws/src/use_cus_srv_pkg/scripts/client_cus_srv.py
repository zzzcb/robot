#! /usr/bin/env python
# coding=utf8

import rospy
from custom_srvs.srv import NumOption, NumOptionRequest, NumOptionResponse

if __name__ == '__main__':
    nodeName = "client_node"
    rospy.init_node(nodeName)

    serviceName = "/zcb01/service"
    client = rospy.ServiceProxy(serviceName, NumOption)
    client.wait_for_service()

    request = NumOptionRequest()
    request.a = 30
    request.b = 20
    request.op = "%"
    try:
        response = client.call(request)
        if isinstance(response, NumOptionResponse):
            rospy.loginfo("call success,result is %d" % response.res)
    except:
        rospy.loginfo("call failed")
