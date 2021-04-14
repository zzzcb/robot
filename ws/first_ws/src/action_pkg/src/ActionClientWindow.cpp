//
// Created by zcb on 4/14/21.
//

#include "ActionClientWindow.h"

ActionClientWindow::ActionClientWindow(ros::NodeHandle *node, QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("action client 控制");

    // timer
    timer = new QTimer(this);
    timer->setInterval(16);
    QTimer::connect(this->timer, &QTimer::timeout, this, &ActionClientWindow::onUpdate);
    timer->start();

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
    QPushButton::connect(this->sendGoalBtn, &QPushButton::clicked, this, &ActionClientWindow::clickSendGoal);
    QPushButton::connect(this->cancelGoalBtn, &QPushButton::clicked, this, &ActionClientWindow::clickCancelGoal);

    // action client
    std::string actionName = "/hello/action";
    this->client = new actionlib::ActionClient<demo_action_msgs::CountNumberAction>(*node, actionName);


}

void ActionClientWindow::clickSendGoal() {

    demo_action_msgs::CountNumberGoal goal;
    goal.goalNum = this->goalNumEdit->text().toInt();
    goal.duration = this->durationEdit->text().toFloat();

    this->goalHandle = this->client->sendGoal(
            goal, bind(&ActionClientWindow::transition_cb, this, _1),
            bind(&ActionClientWindow::feedback_cb, this, _1, _2));

}

void ActionClientWindow::transition_cb(actionlib::ClientGoalHandle<demo_action_msgs::CountNumberAction> handle) {
    // transition 包含了server端 各个阶段响应的状态
    // 两类 ： 1，server 端执行过程的状态CommState  2,server执行完成的状态TerminalState

    actionlib::CommState commState = handle.getCommState();
    if (commState == actionlib::CommState::ACTIVE) { // server active
        ROS_INFO_STREAM("transition cb[CommState][ACTIVE]");

    } else if (commState == actionlib::CommState::DONE) {
        ROS_INFO_STREAM("transition cb[CommState][DONE]");
        this->resultLabel->setText(QString::fromStdString(std::to_string(handle.getResult()->resNum)));

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

void ActionClientWindow::feedback_cb(actionlib::ClientGoalHandle<demo_action_msgs::CountNumberAction> handle,
                                     const demo_action_msgs::CountNumberFeedbackConstPtr &feedback) {
    ROS_INFO_STREAM("feedback: " << feedback->percent * 100 << "%");
    this->percentLabel->setText(QString::fromStdString(std::to_string(feedback->percent * 100) + "%"));

}


void ActionClientWindow::clickCancelGoal() {
    this->goalHandle.cancel();
}


ActionClientWindow::~ActionClientWindow() {

}

void ActionClientWindow::onUpdate() {
    ros::spinOnce();
    this->update();

    if (!ros::ok()) {
        this->close();
    }

}



