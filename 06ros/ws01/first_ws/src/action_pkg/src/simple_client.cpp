//
// Created by zcb on 4/13/21.
//

#include <ros/ros.h>
#include <iostream>
#include <actionlib/client/simple_action_client.h> //for SimpleActionClient
#include <demo_action_msgs/CountNumberAction.h>

using namespace std;


//client.sendGoad() 的三个回调函数
//typedef boost::function<void (const SimpleClientGoalState & state,const ResultConstPtr & result)> SimpleDoneCallback;
//typedef boost::function<void ()> SimpleActiveCallback;
//typedef boost::function<void (const FeedbackConstPtr & feedback)> SimpleFeedbackCallback;

void
doneCallback(const actionlib::SimpleClientGoalState &state, const demo_action_msgs::CountNumberResultConstPtr &result) {
    //  对应 server 中的 server.setSucceeded()
    ROS_INFO_STREAM("[done] result:" << result->resNum);

}

void activeCallback() {
    ROS_INFO_STREAM("[active]");
}

void feedbackCallback(const demo_action_msgs::CountNumberFeedbackConstPtr &feedback) {
    //  对应 server 中的 server.publishFeedback()
    ROS_INFO_STREAM("[feedback] percent:"<<feedback->percent*100<<"%");
}

int main(int argc, char **argv) {

    string nodeName = "simple_action_client_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    string actionName = "/hello/action";
    actionlib::SimpleActionClient<demo_action_msgs::CountNumberAction> client(node, actionName);

    client.waitForServer(); // 等待server启动,还会发送一些状态信息给server ,必须有 !

    demo_action_msgs::CountNumberGoal goal;
    goal.goalNum = 100;
    goal.duration = 0.1;
    client.sendGoal(goal, doneCallback, activeCallback, feedbackCallback);// active ->feedback->done!

    cout << "hello" << endl;
    ros::spin();

    return 0;
}

