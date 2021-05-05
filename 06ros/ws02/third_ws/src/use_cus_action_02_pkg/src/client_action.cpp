//
// Created by zcb on 5/5/21.
//
#include <ros/ros.h>
#include <actionlib/client/action_client.h>
#include <custom_action_msgs/CountNumberAction.h>

void transition_cb(actionlib::ClientGoalHandle<custom_action_msgs::CountNumberAction> handle) {
    const actionlib::CommState state = handle.getCommState();
    if (state == state.ACTIVE) {
        ROS_INFO("ACTIVE");
    } else if (state == state.DONE) {
        const actionlib::TerminalState terminalState = handle.getTerminalState();
        if (terminalState == terminalState.SUCCEEDED) {
            ROS_INFO_STREAM("SUCCEEDED" << terminalState.getText());
        } else if (terminalState == terminalState.ABORTED) {
            ROS_INFO_STREAM("ABORTED" << terminalState.getText());
        } else if (terminalState == terminalState.PREEMPTED) {
            ROS_INFO_STREAM("PREEMPTED" << terminalState.getText());
        } else if (terminalState == terminalState.REJECTED) {
            ROS_INFO_STREAM("REJECTED" << terminalState.getText());
            ROS_INFO_STREAM(terminalState.toString());
        } else if (terminalState == terminalState.RECALLED) {
            ROS_INFO_STREAM("RECALLED" << terminalState.getText());
        }
    } else {
        ROS_INFO_STREAM(state.toString()); // 其他
    }


}

void feedback_cb(actionlib::ClientGoalHandle<custom_action_msgs::CountNumberAction> handle,
                 const custom_action_msgs::CountNumberFeedbackConstPtr &feedback) {
    ROS_INFO_STREAM("feedback_cb " << feedback->rate * 100 << "%");

}


int main(int argc, char **argv) {
    std::string nodeName = "client_node";
    ros::init(argc, argv, nodeName, ros::init_options::AnonymousName);

    ros::NodeHandle node;

    std::string actionName = "/zcb01/action";
    actionlib::ActionClient<custom_action_msgs::CountNumberAction> client(node, actionName);

    ros::AsyncSpinner spinner(1);
    spinner.start();

    client.waitForActionServerToStart(); // wait 内部 开启了一个subscriber ，会阻塞主线程

    custom_action_msgs::CountNumberGoal goal;
    goal.max = 88;
    goal.duration = 0.1;

    // 必须接受返回值,不然不行
    auto handle = client.sendGoal(
            goal, transition_cb, feedback_cb);

    // 3s 后取消任务
//    ros::Duration(3).sleep();
//    handle.cancel();


    ros::waitForShutdown();

    return 0;
}