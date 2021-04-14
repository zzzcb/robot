//
// Created by zcb on 4/13/21.
//

#include "SimpleServerWindow.h"

SimpleServerWindow::SimpleServerWindow(ros::NodeHandle *node, QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("action server控制");
    this->setFixedSize(250, 100);

    timer = new QTimer(this);
    timer->setInterval(16);
    QTimer::connect(this->timer, &QTimer::timeout, this, &SimpleServerWindow::onUpdate);
    timer->start();

    //ui
    this->ly = new QFormLayout(this);
    abortBtn = new QPushButton("模拟server崩溃");
    this->ly->addRow(abortBtn);

    // signal slot
    QPushButton::connect(this->abortBtn, &QPushButton::clicked, this, &SimpleServerWindow::clickAbort);

    // action server
    std::string actionName = "/hello/action";
    server = new actionlib::SimpleActionServer<demo_action_msgs::CountNumberAction>(*node, actionName,
                                                                                    boost::bind(
                                                                                            &SimpleServerWindow::executeCallback,
                                                                                            this, _1), false);
    server->start();

}

void SimpleServerWindow::clickAbort() {
    ROS_INFO_STREAM("模拟server崩溃");
    this->isAborted = true;
}

void SimpleServerWindow::executeCallback(const demo_action_msgs::CountNumberGoalConstPtr &goal) {
    // 回调函数中应该做的事情:
    // 是个耗时操作
    // 1.实时将进度反馈给client
    // 2.如果执行完毕反馈给client
    // 3.如果client取消，就结束执行
    // 4.server 自己能力有限，干不完，自己 abort
    int goalNum = goal->goalNum;
    double duration = goal->duration;

    int cnt = 0;
    bool isCancel = false;
    while (ros::ok() && cnt < goalNum) { // 加上 ros::ok() ，如果中途ctrl+c 可以杀死该程序
        // 检查client是否 取消任务
        if (this->server->isPreemptRequested()) { // 每次都要检测
            isCancel = true;
            break;
        } else if (this->isAborted) { // server 自己abort // 每次都要检测
            break;
        }

        cnt++;
        std::cout << cnt << std::endl;

        //反馈 进度
        demo_action_msgs::CountNumberFeedback feedback;
        feedback.percent = cnt / (goalNum * 1.0);
        this->server->publishFeedback(feedback);


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
        this->server->setPreempted(result); //client cancel
    else if (this->isAborted)
        this->server->setAborted(result); // server aborted
    else
        this->server->setSucceeded(result);

    isAborted = false; // 为下一次使用准备
}

void SimpleServerWindow::onUpdate() {
    ros::spinOnce();
    update();

    if (!ros::ok()) {
        close();
    }
}

SimpleServerWindow::~SimpleServerWindow() {

}


