//
// Created by zcb on 5/4/21.
//

#include <ros/ros.h>
#include <iostream>
#include <custom2_srvs/GenStudentId.h>


int main(int argc, char **argv) {

    std::string nodeName = "client_node";
    ros::init(argc, argv, nodeName);

    ros::NodeHandle node;

    std::string serviceName = "/zcb01/service";
    ros::ServiceClient client = node.serviceClient<custom2_srvs::GenStudentIdRequest, custom2_srvs::GenStudentIdResponse>(
            serviceName);
    client.waitForExistence();


    custom2_srvs::GenStudentId service;
    service.request.stu.name = "tom";
    service.request.stu.age = 18;
    if (client.call(service)) {
        ROS_INFO_STREAM("call success,res is " << service.response.id);
    } else {
        ROS_INFO_STREAM("call failed!");
    }


    return 0;
}





