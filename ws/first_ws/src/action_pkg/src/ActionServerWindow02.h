//
// Created by zcb on 4/14/21.
//

#ifndef ACTION_PKG_ACTIONSERVERWINDOW_H
#define ACTION_PKG_ACTIONSERVERWINDOW_H

#include <ros/ros.h>
#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QTimer>

#include <QTableView>
#include <QStandardItemModel>

#include <actionlib/server/simple_action_server.h>
#include <demo_action_msgs/CountNumberAction.h>

#include <map>

class ActionServerWindow02 : public QWidget {
    Q_OBJECT // 使用信号的使用需要添加 ,这里有个巨坑，此时，.h 和 .cpp 应该放在一个目录，不然会报 vtable 错误，所以这个文件不能放在include目录中了，需要拉回来
public:
    ActionServerWindow02(ros::NodeHandle *node, QWidget *parent = nullptr);

    ~ActionServerWindow02();

private:
    QFormLayout *ly;
    QPushButton *abortBtn; // server 干不动了，
    QTableView *tableView;
    QStandardItemModel *itemModel;

    QTimer *timer;

private:
    void clickAbort();

    void onUpdate();

private:
    actionlib::ActionServer<demo_action_msgs::CountNumberAction> *server;
    bool isAborted = false;
    bool isCancel = false;
private:
    void cancel_cb(actionlib::ServerGoalHandle<demo_action_msgs::CountNumberAction> handle);

    void goal_cb(actionlib::ServerGoalHandle<demo_action_msgs::CountNumberAction> handle);

    void do_goal(actionlib::ServerGoalHandle<demo_action_msgs::CountNumberAction> handle);
private:
    struct ActionItem{
        std::string id;
        bool isCancel; // 客户端是否取消
        bool isAborted; // server 是否断开该客户端
    };
    std::map<std::string,ActionItem*> map_id_action;
private:
    void updateTableUI();
private:
    signals:
    void updateTable();

};

#endif //ACTION_PKG_ACTIONSERVERWINDOW_H
