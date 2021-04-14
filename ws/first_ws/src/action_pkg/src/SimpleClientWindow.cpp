//
// Created by zcb on 4/13/21.
//

#include "SimpleClientWindow.h"

SimpleClientWindow::SimpleClientWindow(ros::NodeHandle *node, QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("action client控制");

    // ui
    this->ly = new QFormLayout(this);
    goalNumEdit = new QLineEdit("100");
    durationEdit = new QLineEdit("0.1");
    percentLabel = new QLabel();
    resultLabel = new QLabel();
    sendGoalBtn = new QPushButton("发送Goal");
    cancelGoalBtn = new QPushButton("取消执行");

    this->ly->addRow("数数数到多少", goalNumEdit);
    this->ly->addRow("数数的间隔", durationEdit);
    this->ly->addRow("server数数的进度", percentLabel);
    this->ly->addRow("server返回的结果", resultLabel);
    this->ly->addRow(sendGoalBtn);
    this->ly->addRow(cancelGoalBtn);

    // signal slot
    QPushButton::connect(this->sendGoalBtn, &QPushButton::clicked, this, &SimpleClientWindow::clickSendGoal);
    QPushButton::connect(this->cancelGoalBtn, &QPushButton::clicked, this, &SimpleClientWindow::clickCancelGoal);


    // action client
    std::string actionName = "/hello/action";
    client = new actionlib::SimpleActionClient<demo_action_msgs::CountNumberAction>(*node, actionName);


}

SimpleClientWindow::~SimpleClientWindow() {

}

void SimpleClientWindow::clickCancelGoal() {
    this->client->cancelGoal();
}



void SimpleClientWindow::clickSendGoal() {
    client->waitForServer(); // 等待server启动,还会发送一些状态信息给server ,必须有 !

    demo_action_msgs::CountNumberGoal goal;
    goal.goalNum = this->goalNumEdit->text().toInt();
    goal.duration = this->durationEdit->text().toFloat();
    client->sendGoal(goal, boost::bind(&SimpleClientWindow::doneCallback, this, _1, _2),
                     boost::bind(&SimpleClientWindow::activeCallback, this),
                     boost::bind(&SimpleClientWindow::feedbackCallback, this, _1));// active ->feedback->done!

}

void SimpleClientWindow::doneCallback(const actionlib::SimpleClientGoalState &state,
                                      const demo_action_msgs::CountNumberResultConstPtr &result) {

    //  state: 1.server完全执行任务 2.server未完全执行任务，client中途取消
    if (state == actionlib::SimpleClientGoalState::SUCCEEDED){  // 成功
        //  对应 server 中的 server.setSucceeded()
        ROS_INFO_STREAM("[done][succeeded] result:" << result->resNum);
    }else if(state == actionlib::SimpleClientGoalState::PREEMPTED){ // 取消
        //  对应 server 中的 server.setPreempted()
        ROS_INFO_STREAM("[done][preempted] result:" << result->resNum);
    }else if(state == actionlib::SimpleClientGoalState::ABORTED) { // server终止
        //  对应 server 中的 server.setAborted()
        ROS_INFO_STREAM("[done][aborted] result:" << result->resNum);
    }

this->resultLabel->setText(QString::fromStdString(std::to_string(result->resNum)));
}

void SimpleClientWindow::activeCallback() {
    ROS_INFO_STREAM("[active]");

}

void SimpleClientWindow::feedbackCallback(const demo_action_msgs::CountNumberFeedbackConstPtr &feedback) {
    //  对应 server 中的 server.publishFeedback()
    ROS_INFO_STREAM("[feedback] percent:" << feedback->percent * 100 << "%");
    this->percentLabel->setText(QString::fromStdString(std::to_string(feedback->percent * 100) + "%"));
}


