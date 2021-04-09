#! /usr/bin/env python
# coding:utf8

import rospy
from demo_srvs.srv import NumOption, NumOptionRequest, NumOptionResponse

if __name__ == '__main__':
    nodeName = "python_client_node"
    rospy.init_node(nodeName)

    serviceName = "/python/service"

    # 与c++ api 不一致，
    client = rospy.ServiceProxy(serviceName, NumOption)
    client.wait_for_service()

    # 与c++ api 不一致,这里只传 request
    request = NumOptionRequest()
    request.a = 10
    request.b = 20
    request.option = "%"

    # 与c++ api 又不一致，艹艹艹艹艹艹
    try:
        response = client.call(request)  # response's type is AddTwoIntsResponse
        if isinstance(response, NumOptionResponse):
            rospy.loginfo("result is %d" % response.result)
    except Exception:
        print("call fail")
