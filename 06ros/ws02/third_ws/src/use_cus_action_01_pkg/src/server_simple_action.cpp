//
// Created by zcb on 5/4/21.
//

#include <actionlib/server/simple_action_server.h>
#include <custom_action_msgs/CountNumberAction.h>
#include <ros/ros.h>

void callback(const custom_action_msgs::CountNumberGoalConstPtr &goal,
              actionlib::SimpleActionServer<custom_action_msgs::CountNumberAction> *server) {
    // 1.实时将进度反馈给client
    // 2.如果执行完毕反馈给client
    // 3.如果client取消，就结束执行
    // 4.server 自己能力有限，干不完，自己abort
    int max = goal->max;
    double duration = goal->duration;

    int cnt = 0; // 从0 开始数数 ,数到 max
    ros::Duration dur(duration);
    bool isCancel = false;
//    bool isAborted = false;
    while (ros::ok() && cnt < max) {
        // 3 检测client 是否取消
        if (server->isPreemptRequested()) {
            isCancel = true;
            break;
        }
        // 4 server 自己崩了
//        if (cnt > 20) {
//            isAborted = true; // 一般情况下,server端 点击 之后 设置isAbort 为 true
//            break;
//        }

        cnt++;
        ROS_INFO_STREAM(cnt);

        //1. 反馈进度
        custom_action_msgs::CountNumberFeedback feedback;
        feedback.rate = cnt / (max * 1.0);
        server->publishFeedback(feedback);


        dur.sleep();
    }
    //2. 反馈结果
    custom_action_msgs::CountNumberResult result;
    result.result = cnt;
    if (isCancel) {
        server->setPreempted(result);
        isCancel = false;
//    } else if (isAborted) {
//        server->setAborted(result);
//        isAborted = false;
    } else {
        server->setSucceeded(result);
    }


}

int main(int argc, char **argv) {
    std::string nodeName = "server_node";
    ros::init(argc, argv, nodeName);

    ros::NodeHandle node;

    std::string actionName = "/zcb01/action";
    actionlib::SimpleActionServer<custom_action_msgs::CountNumberAction> server(
            node, actionName, bind(callback, _1, &server), false);
    server.start();

    ros::spin();


    return 0;
}

