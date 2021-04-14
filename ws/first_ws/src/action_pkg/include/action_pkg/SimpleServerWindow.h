//
// Created by zcb on 4/13/21.
//

#ifndef ACTION_PKG_SIMPLESERVERWINDOW_H
#define ACTION_PKG_SIMPLESERVERWINDOW_H

#include <ros/ros.h>
#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QTimer>

#include <actionlib/server/simple_action_server.h>
#include <demo_action_msgs/CountNumberAction.h>

class SimpleServerWindow : public QWidget {
public:
    SimpleServerWindow(ros::NodeHandle* node, QWidget *parent = nullptr);

    ~SimpleServerWindow();

private:
    QFormLayout *ly;
    QPushButton *abortBtn; // server 干不动了，

    QTimer* timer;

private:
    void clickAbort();
    void onUpdate();

private:
    actionlib::SimpleActionServer<demo_action_msgs::CountNumberAction> *server;
    bool isAborted = false;
private:
    void executeCallback(const demo_action_msgs::CountNumberGoalConstPtr &goal);


};


#endif //ACTION_PKG_SIMPLESERVERWINDOW_H
