//
// Created by zcb on 21-9-10.
//

#include "hello_pkg/fuck.h"

#include <std_msgs/String.h>
#include <pluginlib/class_list_macros.h>


namespace hello_pkg_ns {
    void Fuck::onInit() {
        nh_ = ros::NodeHandle();
        pub_ = nh_.advertise<std_msgs::String>("topic", 10);
        timer_ = nh_.createTimer(ros::Duration(1.0), boost::bind(&Fuck::timerCb, this));
        cnt_ = 0;
    }

    void Fuck::timerCb() {
        std_msgs::String msg;
        msg.data = "zzzcb " + std::to_string(cnt_++);
        pub_.publish(msg);
    }
}

PLUGINLIB_EXPORT_CLASS(hello_pkg_ns::Fuck, nodelet::Nodelet)
