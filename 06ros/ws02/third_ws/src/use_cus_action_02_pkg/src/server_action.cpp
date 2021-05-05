//
// Created by zcb on 5/5/21.
//

#include <ros/ros.h>
#include <actionlib/server/action_server.h>
#include <custom_action_msgs/CountNumberAction.h>
#include <thread>

bool isCancel = false;
//bool isAborted = false;

void do_goal(actionlib::ServerGoalHandle<custom_action_msgs::CountNumberAction> handle) {
    auto goal = handle.getGoal();
    int max = goal->max;
    double duration = goal->duration;

    custom_action_msgs::CountNumberResult result;

    if (max < 0 || max > 100) { // REJECTED
        handle.setRejected(result, " max should in (0,100] [zcb]");
        return;
    } else {
        handle.setAccepted();
    }

    int cnt = 0; // 从0 开始数数 ,数到 max
    ros::Duration dur(duration);
    while (ros::ok() && cnt < max) {
        // 3 检测client 是否取消
        if (isCancel) {
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
        handle.publishFeedback(feedback);


        dur.sleep();
    }
    //2. 反馈结果
    result.result = cnt;
    if (isCancel) {
        handle.setCanceled(result, " client cancel[zcb]");
        isCancel = false;
//    } else if (isAborted) {
//        handle.setAborted(result," server aborted[zcb]");
//        isAborted = false;
    } else {
        handle.setSucceeded(result, " success [zcb]");
    }

}

void goal_cb(actionlib::ServerGoalHandle<custom_action_msgs::CountNumberAction> handle) {
    std::thread t(do_goal, handle);
    t.detach(); // 不 阻塞 主线程

    // 1.实时将进度反馈给client
    // 2.如果执行完毕反馈给client
    // 3.如果client取消，就结束执行
    // 4.server 自己能力有限，干不完，自己abort

}

void cancel_cb(actionlib::ServerGoalHandle<custom_action_msgs::CountNumberAction> handle) {
    ROS_INFO("cancel cb");
    isCancel = true;
}

int main(int argc, char **argv) {

    std::string nodeName = "server_node";
    ros::init(argc, argv, nodeName);

    ros::NodeHandle node;

    std::string actionName = "/zcb01/action";
    // goal_cb 内会阻塞 主线程,所以需要多线程
    actionlib::ActionServer<custom_action_msgs::CountNumberAction> server(node,
                                                                          actionName,
                                                                          goal_cb,
                                                                          cancel_cb, false);

    server.start();

    ros::spin();

    return 0;
}