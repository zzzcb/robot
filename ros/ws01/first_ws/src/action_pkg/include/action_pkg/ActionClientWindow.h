//
// Created by zcb on 4/14/21.
//

#ifndef ACTION_PKG_ACTIONCLIENTWINDOW_H
#define ACTION_PKG_ACTIONCLIENTWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <actionlib/client/action_client.h>
#include <demo_action_msgs/CountNumberAction.h>

#include <ros/ros.h>


class ActionClientWindow : public QWidget {
public:
    ActionClientWindow(ros::NodeHandle *node, QWidget *parent = nullptr);

    ~ActionClientWindow();

private:
    QTimer *timer;
    QFormLayout *ly;
    QLineEdit *goalNumEdit, *durationEdit;
    QPushButton *sendGoalBtn;
    QPushButton *cancelGoalBtn;
    QLabel *percentLabel, *resultLabel; // 进度 和 结果 展示

private:
    void onUpdate();

    void clickSendGoal();

    void clickCancelGoal();

private:
    actionlib::ActionClient<demo_action_msgs::CountNumberAction> *client;
    actionlib::ActionClient<demo_action_msgs::CountNumberAction>::GoalHandle goalHandle; //用于 cancel
private:
    void feedback_cb(actionlib::ClientGoalHandle<demo_action_msgs::CountNumberAction> handle,
                     const demo_action_msgs::CountNumberFeedbackConstPtr &feedback);

    void transition_cb(actionlib::ClientGoalHandle<demo_action_msgs::CountNumberAction> handle);


};


#endif //ACTION_PKG_ACTIONCLIENTWINDOW_H
