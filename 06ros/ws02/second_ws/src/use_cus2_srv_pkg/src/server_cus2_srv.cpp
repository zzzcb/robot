//
// Created by zcb on 5/4/21.
//

#include <ros/ros.h>
#include <iostream>
#include <custom2_srvs/GenStudentId.h>


bool callback(custom2_srvs::GenStudentIdRequest &request, custom2_srvs::GenStudentIdResponse &response) {
    response.id = "000" + request.stu.name + "111" + std::to_string(request.stu.age) + "000";

    return true;
}


int main(int argc, char **argv) {

    std::string nodeName = "server_node";
    ros::init(argc, argv, nodeName);

    ros::NodeHandle node;

    std::string serviceName = "/zcb01/service";
    ros::ServiceServer server = node.advertiseService(serviceName, callback);

    ros::spin();


    return 0;
}

