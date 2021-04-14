//
// Created by zcb on 4/14/21.
//

#include "ActionServerWindow.h"
#include <thread>

ActionServerWindow::ActionServerWindow(ros::NodeHandle *node, QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("action server 控制");
    this->setFixedSize(250, 100);


    // timer
    timer = new QTimer(this);
    timer->setInterval(16);
    QTimer::connect(this->timer, &QTimer::timeout, this, &ActionServerWindow::onUpdate);
    timer->start();

    // ui
    this->ly = new QFormLayout(this);
    abortBtn = new QPushButton("模拟server崩溃");
    this->ly->addRow(abortBtn);

    // signal slot
    QPushButton::connect(this->abortBtn, &QPushButton::clicked, this, &ActionServerWindow::clickAbort);



    // action server
    std::string actionName = "/hello/action";
    // 注: goal_bk 和 cancel_bk 是在主线程中执行的，需要多线程，
    this->server = new actionlib::ActionServer<demo_action_msgs::CountNumberAction>(*node, actionName,
                                                                                    bind(&ActionServerWindow::goal_cb,
                                                                                         this, _1),
                                                                                    bind(&ActionServerWindow::cancel_cb,
                                                                                         this, _1),
                                                                                    false);
    this->server->start();

}

void ActionServerWindow::clickAbort() {
    std::cout << "模拟server 崩溃" << std::endl;
    this->isAborted = true;

}

void ActionServerWindow::goal_cb(actionlib::ServerGoalHandle<demo_action_msgs::CountNumberAction> handle) {
    //cout << "goal cb" << endl;
    // 1 业务处理 (还是数数)
    // 2 进度的返回
    // 3 结果的返回
    // 4 client 的cacel操作
    // 5 server 的abort操作

    // 耗时操作，开启子线程 去执行任务
    new std::thread(bind(&ActionServerWindow::do_goal, this, handle));

}

void ActionServerWindow::do_goal(actionlib::ServerGoalHandle<demo_action_msgs::CountNumberAction> handle) {
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
        if (this->isCancel) { // 使用 简单的flag  不太好，比如一个server，多个client，我们点一下中止,所有client都断开了；一个client取消 很可能将所有的client都取消了 ~ 下个版本中改善 见ActionServerWindow02
            break;
        }else if(this->isAborted){ // 5 中断操作 每次都检测
            break;
        }


        // 1,业务处理
        cnt++;
        std::cout << cnt << std::endl;

        // 2,进度的返回
        feedback.percent = cnt * 1.0 / goalNum;
        handle.publishFeedback(feedback);

        dur.sleep();
    }
    // 3 结果的返回
    demo_action_msgs::CountNumberResult result;
    result.resNum = cnt;
    if (this->isCancel) { // 4 取消
        this->isCancel = false;
        handle.setCanceled(result);
    } else if(this->isAborted) { // 5 中断
        this->isAborted = false;
        handle.setAborted(result);
    } else {
        handle.setSucceeded(result);
    }


}


void ActionServerWindow::cancel_cb(actionlib::ServerGoalHandle<demo_action_msgs::CountNumberAction> handle) {
    std::cout << "cancel cb" << std::endl;
    this->isCancel = true;
}


ActionServerWindow::~ActionServerWindow() {

}

void ActionServerWindow::onUpdate() {
    ros::spinOnce();
    this->update();

    if (!ros::ok()) {
        this->close();
    }
}







