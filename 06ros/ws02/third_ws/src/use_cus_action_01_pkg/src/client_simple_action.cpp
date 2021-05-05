//
// Created by zcb on 5/4/21.
//
#include <actionlib/client/simple_action_client.h>
#include <custom_action_msgs/CountNumberAction.h>
#include <ros/ros.h>

void done_callback(
        const actionlib::SimpleClientGoalState &state,
        const custom_action_msgs::CountNumberResultConstPtr &result
) {
    if (state == state.ABORTED) {
        ROS_INFO("server working error, don't finish my job.");
    } else if (state == state.PREEMPTED) {
        ROS_INFO("client cancel job.");
    } else if (state == state.SUCCEEDED) {
        ROS_INFO("server finish job.");
        ROS_INFO_STREAM("[done] result:" << result->result);
    }


}

void active_callback() {
    ROS_INFO_STREAM("[active]");
}

void fb_callback(
        const custom_action_msgs::CountNumberFeedbackConstPtr &feedback) {
    ROS_INFO_STREAM("[feedback] percent:" << feedback->rate * 100 << "%");
}


int main(int argc, char **argv) {
    std::string nodeName = "client_node";
    ros::init(argc, argv, nodeName);

    ros::NodeHandle node;

    std::string actionName = "/zcb01/action";
    actionlib::SimpleActionClient<custom_action_msgs::CountNumberAction> client(node, actionName);
    client.waitForServer();

    custom_action_msgs::CountNumberGoal goal;
    goal.max = 111;
    goal.duration = 0.1;

    client.sendGoal(goal, done_callback, active_callback, fb_callback);

//    ros::Duration(3).sleep(); // 3 s 后 取消任务
//    client.cancelGoal();

    ros::spin();

    return 0;
}
