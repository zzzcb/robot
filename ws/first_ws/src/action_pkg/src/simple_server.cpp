//
// Created by zcb on 4/13/21.
//

#include <iostream>
#include <ros/ros.h>

#include <actionlib/server/simple_action_server.h> // 引入 action的头,CMakeLists中的find要加上 actionlib,这和自定义时的actionlib_msgs不一样
#include <demo_action_msgs/CountNumberAction.h>

using namespace std;

void executeCallback(const demo_action_msgs::CountNumberGoalConstPtr &goal,
                     actionlib::SimpleActionServer<demo_action_msgs::CountNumberAction> *server) {
    // 回调函数中应该做的事情:
    // 是个耗时操作
    // 1.实时将进度反馈给client
    // 2.如果执行完毕反馈给client
    // 3.如果client取消，就结束执行
    // 4.server 自己能力有限，干不完，自己abort

    int goalNum = goal->goalNum;
    double duration = goal->duration;

    int cnt = 0;
    bool isCancel = false;
    while (ros::ok() && cnt < goalNum) { // 加上 ros::ok() ，如果中途ctrl+c 可以杀死该程序
        // 检查client是否 取消任务
        if (server->isPreemptRequested()) { // 每次都要检测
            isCancel = true;
            break;
        }

        cnt++;
        cout << cnt << endl;

        //反馈 进度
        demo_action_msgs::CountNumberFeedback feedback;
        feedback.percent = cnt / (goalNum * 1.0);
        server->publishFeedback(feedback);


        // 睡眠 不要用c++的sleep，用ros自带的 ros::Rate 或者 ros::Duration
        //ros::Rate rate(1/duration); // 睡 duration
        //rate.sleep();
        // 或者
        ros::Duration dur(duration);
        dur.sleep();  // 睡 duration
    }

    // 反馈 结果
    demo_action_msgs::CountNumberResult result;
    result.resNum = cnt;

    if (isCancel)
        server->setPreempted(result); //client cancel
    else
        server->setSucceeded(result);

}


int main(int argc, char **argv) {
    //init node
    string nodeName = "simple_action_server_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    // action
    string actionName = "/hello/action"; // function<void (const GoalConstPtr &)> ExecuteCallback;
    actionlib::SimpleActionServer<demo_action_msgs::CountNumberAction> server(node, actionName,
                                                                              bind(executeCallback, _1, &server),
                                                                              false);
    server.start();

    ros::spin();

    return 0;
}