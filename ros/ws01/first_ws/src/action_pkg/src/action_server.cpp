//
// Created by zcb on 4/14/21.
//

#include <iostream>
#include <ros/ros.h>
#include <actionlib/server/action_server.h>
#include <demo_action_msgs/CountNumberAction.h>
#include <thread>

using namespace std;

bool isCancel = false;

void do_goal(actionlib::ServerGoalHandle<demo_action_msgs::CountNumberAction> handle) {

    int goalNum = handle.getGoal()->goalNum;
    float duration = handle.getGoal()->duration;
    // 1 业务处理（校验数据）
    if (goalNum <= 0 || duration <= 0) { // 数据不符合规范
        // ### SERVER STATE:Rejected
        handle.setRejected(); // 手动设置
        return;
    }
    // 数据符合规范
    // ### SERVER STATE:Accepted
    handle.setAccepted(); // 手动设置

    demo_action_msgs::CountNumberFeedback feedback;

    int cnt = 0;
    ros::Duration dur(duration);
    while (ros::ok() && cnt < goalNum) {
        // 4 取消操作 每次都检测
        if (isCancel) {
            break;
        }


        // 1,业务处理
        cnt++;
        cout << cnt << endl;

        // 2,进度的返回
        feedback.percent = cnt * 1.0 / goalNum;
        handle.publishFeedback(feedback);

        dur.sleep();
    }
    // 3 结果的返回
    demo_action_msgs::CountNumberResult result;
    result.resNum = cnt;
    if (isCancel) { // 4 取消
        isCancel = false;
        handle.setCanceled(result);
    } else {
        handle.setSucceeded(result);
    }


}

void goal_cb(actionlib::ServerGoalHandle<demo_action_msgs::CountNumberAction> handle) {
    //cout << "goal cb" << endl;
    // 1 业务处理 (还是数数)
    // 2 进度的返回
    // 3 结果的返回
    // 4 client 的cacel操作
    // 5 server 的abort操作 (oop中去做)

    // 耗时操作，开启子线程 去执行任务
    new thread(do_goal, handle);


}

void cancel_cb(actionlib::ServerGoalHandle<demo_action_msgs::CountNumberAction> handle) {
    cout << "cancel cb" << endl;
    isCancel = true;
}

int main(int argc, char **argv) {

    string nodeName = "action_server_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    string actionName = "/hello/action";
    // 注: goal_bk 和 cancel_bk 是在主线程中执行的，需要多线程，
    actionlib::ActionServer<demo_action_msgs::CountNumberAction> server(node, actionName, goal_cb, cancel_cb, false);

    server.start();


    ros::spin();
}








