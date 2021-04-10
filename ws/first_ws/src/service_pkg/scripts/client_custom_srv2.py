#! /usr/bin/env python
# coding:utf8

import rospy
from demo_srvs.srv import GetStudentId, GetStudentIdRequest, GetStudentIdResponse

if __name__ == '__main__':
    nodeName = "python_client_node"
    rospy.init_node(nodeName)

    serviceName = "/python/service"

    # 与c++ api 不一致，
    client = rospy.ServiceProxy(serviceName, GetStudentId)
    client.wait_for_service()

    # 与c++ api 不一致,这里只传 request
    request = GetStudentIdRequest()
    request.stu.name = "fuck"
    request.stu.age = 18

    # 与c++ api 又不一致，艹艹艹艹艹艹
    try:
        response = client.call(request)
        if isinstance(response, GetStudentIdResponse):
            rospy.loginfo("result is %s" % response.id)
    except Exception as e:
        print(e.message)
        print("call fail")
