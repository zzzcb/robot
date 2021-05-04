//
// Created by zcb on 5/4/21.
//

#include <ros/ros.h>
#include <iostream>
#include <roscpp_tutorials/TwoInts.h>


int main(int argc, char **argv) {

    std::string nodeName = "client_node";
    ros::init(argc, argv, nodeName);

    ros::NodeHandle node;

    std::string serviceName = "/zcb01/service";
    ros::ServiceClient client = node.serviceClient<roscpp_tutorials::TwoIntsRequest, roscpp_tutorials::TwoIntsResponse>(
            serviceName);
    client.waitForExistence();


    roscpp_tutorials::TwoInts service;
    service.request.a = 10;
    service.request.b = 13;
    if (client.call(service)) {
        ROS_INFO_STREAM("call success,res is " << service.response.sum);
    }else{
        ROS_INFO_STREAM("call failed!");
    }


    return 0;
}





