//
// Created by zcb on 4/13/21.
//

#ifndef ACTION_PKG_SIMPLECLIENTWINDOW_H
#define ACTION_PKG_SIMPLECLIENTWINDOW_H

#include <ros/ros.h>
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include <actionlib/client/simple_action_client.h> //for SimpleActionClient
#include <demo_action_msgs/CountNumberAction.h>

class SimpleClientWindow : public QWidget {
public:
    SimpleClientWindow(ros::NodeHandle *node, QWidget *parent = nullptr);

    ~SimpleClientWindow();

private:
    QFormLayout *ly;
    QLineEdit *goalNumEdit, *durationEdit;
    QPushButton *sendGoalBtn;
    QPushButton *cancelGoalBtn;
    QLabel *percentLabel, *resultLabel; // 进度 和 结果 展示

private:
    void clickSendGoal();
    void clickCancelGoal();

private:
    actionlib::SimpleActionClient<demo_action_msgs::CountNumberAction> *client;

private:
    void
    doneCallback(const actionlib::SimpleClientGoalState &state,
                 const demo_action_msgs::CountNumberResultConstPtr &result);

    void activeCallback();

    void feedbackCallback(const demo_action_msgs::CountNumberFeedbackConstPtr &feedback);

};


#endif //ACTION_PKG_SIMPLECLIENTWINDOW_H
