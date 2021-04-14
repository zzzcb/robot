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

#include <actionlib/server/simple_action_server.h>
#include <demo_action_msgs/CountNumberAction.h>

class ActionServerWindow : public QWidget {
public:
    ActionServerWindow(ros::NodeHandle *node, QWidget *parent = nullptr);

    ~ActionServerWindow();

private:
    QFormLayout *ly;
    QPushButton *abortBtn; // server 干不动了，

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


};

#endif //ACTION_PKG_ACTIONSERVERWINDOW_H
