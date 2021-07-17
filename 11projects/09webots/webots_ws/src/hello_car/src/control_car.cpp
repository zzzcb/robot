//
// Created by zcb on 7/15/21.
//

#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>

#include <webots_ros/set_float.h>
#include <webots_ros/set_int.h>

using namespace std;

int cnt = 0;
string motor_names[4] = {"front_left_wheel_motor", "front_right_wheel_motor", "behind_left_wheel_motor",
                         "behind_right_wheel_motor",};

void model_name_cb(const std_msgs::String::ConstPtr &msg) {
    cnt++;
    cout << "webots 仿真已经启动" << cnt << endl;
}

void updateSpeed(ros::NodeHandle &node, double velocity) {
    for (int i = 0; i < 4; ++i) {
        //设置 init position
        ros::ServiceClient set_velocity_client;
        webots_ros::set_float set_velocity_srv;
        set_velocity_client = node.serviceClient<webots_ros::set_float>(
                "/my4x4car/" + motor_names[i] + "/set_velocity");
        set_velocity_srv.request.value = velocity;
        if (set_velocity_client.call(set_velocity_srv) && set_velocity_srv.response.success)
            ROS_INFO_STREAM("motor " << motor_names[i] << "set velocity sucess");
        else
            ROS_ERROR_STREAM("motor " << motor_names[i] << "set velocity failed");
    }
}

int main(int argc, char **argv) {

    //1 ros node init
    std::string nodeName = "control_my4x4car_node";
    ros::init(argc, argv, nodeName);

    ros::NodeHandle node;


    //2 判断是否webots启动,通过订阅/model_name ,webots 启动会发布该topic
    std::string topicName = "/model_name";
    ros::Subscriber nameSub = node.subscribe(topicName, 100, model_name_cb);
    while (cnt == 0) {
        ros::spinOnce();
    }
    nameSub.shutdown();

    //3 初始化 设备

    for (int i = 0; i < 4; ++i) {
        //设置 init position
        ros::ServiceClient set_position_client;
        webots_ros::set_float set_position_srv;
        set_position_client = node.serviceClient<webots_ros::set_float>(
                "/my4x4car/" + motor_names[i] + "/set_position");
        set_position_srv.request.value = INFINITY;
        if (set_position_client.call(set_position_srv) && set_position_srv.response.success)
            ROS_INFO_STREAM("motor " << motor_names[i] << "set position sucess");
        else
            ROS_ERROR_STREAM("motor " << motor_names[i] << "set position failed");

        // 设置 init velocity
        ros::ServiceClient set_velocity_client;
        webots_ros::set_float set_velocity_srv;
        set_velocity_client = node.serviceClient<webots_ros::set_float>(
                "/my4x4car/" + motor_names[i] + "/set_velocity");
        set_velocity_srv.request.value = 0.0;
        if (set_velocity_client.call(set_velocity_srv) && set_velocity_srv.response.success)
            ROS_INFO_STREAM("motor " << motor_names[i] << "set velocity sucess");
        else
            ROS_ERROR_STREAM("motor " << motor_names[i] << "set velocity failed");
    }

    //4 主循环
    ros::Rate rate(10);
    while (ros::ok()) {
        updateSpeed(node, 1.0); // 更新小车速度

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}

