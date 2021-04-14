//
// Created by zcb on 4/14/21.
//

#include <iostream>
#include <ros/ros.h>

#include <actionlib/client/action_client.h>
#include <demo_action_msgs/CountNumberAction.h>

using namespace std;


void transition_cb(actionlib::ClientGoalHandle<demo_action_msgs::CountNumberAction> handle) {
    // transition 包含了server端 各个阶段响应的状态
    // 两类 ： 1，server 端执行过程的状态CommState  2,server执行完成的状态TerminalState

    actionlib::CommState commState = handle.getCommState();
    if (commState == actionlib::CommState::ACTIVE) { // server active
        ROS_INFO_STREAM("transition cb[CommState][ACTIVE]");

    } else if (commState == actionlib::CommState::DONE) {
        ROS_INFO_STREAM("transition cb[CommState][DONE]");

        // TerminalState
        actionlib::TerminalState terminalState = handle.getTerminalState();
        if (terminalState == actionlib::TerminalState::SUCCEEDED) { // server 成功
            ROS_INFO_STREAM("transition cb[TerminalState][SUCCEEDED]");

        } else if (terminalState == actionlib::TerminalState::PREEMPTED) {// client取消
            ROS_INFO_STREAM("transition cb[TerminalState][PREEMPTED]");

        } else if (terminalState == actionlib::TerminalState::ABORTED) {// server 中断
            ROS_INFO_STREAM("transition cb[TerminalState][ABORTED]");

        } else if (terminalState == actionlib::TerminalState::REJECTED) {// server 拒绝
            ROS_INFO_STREAM("transition cb[TerminalState][REJECTED]");
        }

    }


}

void feedback_cb(actionlib::ClientGoalHandle<demo_action_msgs::CountNumberAction> handle,
                 const demo_action_msgs::CountNumberFeedbackConstPtr &feedback) {
    ROS_INFO_STREAM("feedback: " << feedback->percent * 100 << "%");
}

int main(int argc, char **argv) {

    string nodeName = "action_client_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    string actionName = "/hello/action";
    actionlib::ActionClient<demo_action_msgs::CountNumberAction> client(node, actionName);

    client.waitForActionServerToStart(); // 等待启动，内部开启了一个subsciber,阻塞了主线程,

    demo_action_msgs::CountNumberGoal goal;
    goal.goalNum = 100;
    goal.duration = 0.1;
    // client.sendGoal() 必须接受，不然就被垃圾回收掉了
    actionlib::ActionClient<demo_action_msgs::CountNumberAction>::GoalHandle handle = client.sendGoal(goal,
                                                                                                      transition_cb,
                                                                                                      feedback_cb);

    // 3s 后取消任务
    ros::Duration(3).sleep();
    handle.cancel();

    spinner.stop();
    ros::spin();
    //ros::waitForShutdown();

}

