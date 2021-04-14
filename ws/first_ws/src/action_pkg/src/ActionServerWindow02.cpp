//
// Created by zcb on 4/14/21.
//

#include "ActionServerWindow02.h"
#include <thread>

ActionServerWindow02::ActionServerWindow02(ros::NodeHandle *node, QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("action server 控制");


    // timer
    timer = new QTimer(this);
    timer->setInterval(16);
    QTimer::connect(this->timer, &QTimer::timeout, this, &ActionServerWindow02::onUpdate);
    timer->start();

    // ui
    this->ly = new QFormLayout(this);
    abortBtn = new QPushButton("模拟server崩溃");
    this->ly->addRow(abortBtn);

    tableView = new QTableView();
    itemModel = new QStandardItemModel();
    tableView->setModel(itemModel);
    this->ly->addRow(tableView);

    this->itemModel->setColumnCount(2);
    this->itemModel->setHeaderData(0, Qt::Horizontal, "ID");
    this->itemModel->setHeaderData(1, Qt::Horizontal, "操作");







    // signal slot
    QPushButton::connect(this->abortBtn, &QPushButton::clicked, this, &ActionServerWindow02::clickAbort);
    ActionServerWindow02::connect(this,&ActionServerWindow02::updateTable,this,&ActionServerWindow02::updateTableUI); // 自定义信号 ,自己发自己收




    // action server
    std::string actionName = "/hello/action";
    // 注: goal_bk 和 cancel_bk 是在主线程中执行的，需要多线程，
    this->server = new actionlib::ActionServer<demo_action_msgs::CountNumberAction>(*node, actionName,
                                                                                    bind(&ActionServerWindow02::goal_cb,
                                                                                         this, _1),
                                                                                    bind(&ActionServerWindow02::cancel_cb,
                                                                                         this, _1),
                                                                                    false);
    this->server->start();

}

void ActionServerWindow02::clickAbort() {
    std::cout << "模拟server 崩溃" << std::endl;
    this->isAborted = true;

}

void ActionServerWindow02::updateTableUI() {

    this->itemModel->clear(); // 每次都应该clear,不然会有缓存

    this->itemModel->setColumnCount(2);
    this->itemModel->setHeaderData(0, Qt::Horizontal, "ID");
    this->itemModel->setHeaderData(1, Qt::Horizontal, "操作");


    std::map<std::string, ActionItem *> m = this->map_id_action;
    int row = 0;
    for (auto item = m.begin(); item != m.end(); item++) {
        this->itemModel->setItem(row, 0, new QStandardItem(QString::fromStdString(item->second->id)));
        this->itemModel->setItem(row, 1, new QStandardItem());//item中要放个btn,下面两行实现

        QPushButton *btn = new QPushButton("中止");

        QPushButton::connect(btn, &QPushButton::clicked, this, [item] { // 匿名 signal slot
            item->second->isAborted = true;
        });
        this->tableView->setIndexWidget(this->itemModel->index(row, 1), btn);

        row++;
    }


}

void ActionServerWindow02::goal_cb(actionlib::ServerGoalHandle<demo_action_msgs::CountNumberAction> handle) {
    // 每次来的 handle 都对应一个client，是唯一的，类似与Django中的request
    // 可以使用map<id,obj> 这种结构来保存  id要唯一

    std::string id = handle.getGoalID().id;// 它是唯一的
    ActionItem *item = new ActionItem();// 来一个client,添加map 中一个
    item->id = id;
    item->isCancel = false;
    item->isAborted = false;
    this->map_id_action.insert({id, item});

    this->updateTableUI(); // 更新TableUI

    // 1 业务处理 (还是数数)
    // 2 进度的返回
    // 3 结果的返回
    // 4 client 的cacel操作
    // 5 server 的abort操作

    // 耗时操作，开启子线程 去执行任务
    new std::thread(bind(&ActionServerWindow02::do_goal, this, handle));

}

void ActionServerWindow02::do_goal(actionlib::ServerGoalHandle<demo_action_msgs::CountNumberAction> handle) {
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
    ActionItem *item = this->map_id_action.at(handle.getGoalID().id);

    int cnt = 0;
    ros::Duration dur(duration);
    while (ros::ok() && cnt < goalNum) {
        // 4 取消操作 每次都检测
        if (item->isCancel) {
            break;
        } else if (item->isAborted) {
            break;
        }

        /*
        if (this->isCancel) {  // 全局
            break;
        } else if (this->isAborted) {  // 全局
            break;
        }
         */


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
    /* 全局
    if (this->isCancel) { // 4 取消
        this->isCancel = false;
        handle.setCanceled(result);
    } else if (this->isAborted) { // 5 中断
        this->isAborted = false;
        handle.setAborted(result);
    } else {
        handle.setSucceeded(result);
    }*/

    if (item->isCancel) { // 4 取消
        // 从map 中移除 该 item
        //map_id_action.erase(item->id);
        handle.setCanceled(result);
    } else if (item->isAborted) { // 5 中断
        //map_id_action.erase(item->id);
        handle.setAborted(result);
    } else {
        //map_id_action.erase(item->id);
        handle.setSucceeded(result);
    }
    map_id_action.erase(item->id);
    // 再次更新UI table ，因为该item已经移除了，
//    this->updateTableUI();  // 但是QT 不能在子线程中更新UI,解决方法是手动触发一个信号,
    emit this->updateTable(); // 发送信号


}


void ActionServerWindow02::cancel_cb(actionlib::ServerGoalHandle<demo_action_msgs::CountNumberAction> handle) {
    std::cout << "cancel cb" << std::endl;
    this->isCancel = true; // 全局的
    ActionItem *item = this->map_id_action.at(handle.getGoalID().id);
    item->isCancel = true; // 单独的

}


ActionServerWindow02::~ActionServerWindow02() {

}

void ActionServerWindow02::onUpdate() {
    ros::spinOnce();
    this->update();

    if (!ros::ok()) {
        this->close();
    }
}







