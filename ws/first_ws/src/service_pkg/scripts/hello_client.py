#! /usr/bin/env python
# coding:utf8

import rospy
from rospy_tutorials.srv import AddTwoInts, AddTwoIntsRequest, AddTwoIntsResponse

if __name__ == '__main__':
    nodeName = "python_client_node"
    rospy.init_node(nodeName)

    serviceName = "/python/service"

    # 与c++ api 不一致，
    client = rospy.ServiceProxy(serviceName, AddTwoInts)
    client.wait_for_service()

    # 与c++ api 不一致,这里只传 request
    request = AddTwoIntsRequest()
    request.a = 10
    request.b = 20

    # 与c++ api 又不一致，艹艹艹艹艹艹
    response = client.call(request)  # response's type is AddTwoIntsResponse
    if isinstance(response, AddTwoIntsResponse):
        rospy.loginfo("result is %d" % response.sum)
