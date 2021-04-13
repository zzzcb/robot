//
// Created by zcb on 2021/4/11.
//

#include "FinalPosWindow2.h"
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <thread>

FinalPosWindow2::FinalPosWindow2(ros::NodeHandle *node, QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("小乌龟控制");

    this->timer = new QTimer(this);
    this->timer->setInterval(16); // 16ms
    this->timer->start();
    QTimer::connect(this->timer, &QTimer::timeout, this, &FinalPosWindow2::onUpdate);

    // ui
    this->formlayout = new QFormLayout(this);

    this->finalPosX = new QLineEdit("10.54");
    this->finalPosY = new QLineEdit("5.54");
    this->kpEditLine = new QLineEdit("0.1");
    this->kiEditLine = new QLineEdit("0.1");
    this->kdEditLine = new QLineEdit("0.1");
    this->sendBtn = new QPushButton("执行");
    this->sweepVBtn = new QPushButton("纵向扫地");

    this->formlayout->addRow("目标位置X", finalPosX);
    this->formlayout->addRow("目标位置Y", finalPosY);
    this->formlayout->addRow("kp系数", this->kpEditLine);
    this->formlayout->addRow("ki系数", this->kiEditLine);
    this->formlayout->addRow("kd系数", this->kdEditLine);
    this->formlayout->addRow(this->sendBtn);
    this->formlayout->addRow(this->sweepVBtn);

    // event:sendBtn
    QPushButton::connect(this->sendBtn, &QPushButton::clicked, this, &FinalPosWindow2::sendMsgEvt);
    QPushButton::connect(this->sweepVBtn, &QPushButton::clicked, this, &FinalPosWindow2::clickSweepV);

    // publisher
    std::string velTopicName = "/turtle1/cmd_vel";
    this->velPublisher = node->advertise<geometry_msgs::Twist>(velTopicName, 1000);

    std::string plotVelTopicName = "/plot/vel";
    this->plotVelPublisher = node->advertise<std_msgs::Float64>(plotVelTopicName, 1000);

    // subscriber
    std::string posTopicName = "/turtle1/pose";
    this->posSubscriber = node->subscribe(posTopicName, 1000, &FinalPosWindow2::poseCallback, this);


}

FinalPosWindow2::~FinalPosWindow2() {


}

void FinalPosWindow2::clickSweepV() {
    // 构建 路点
    // (2,2) (2,10)
    // ...
    // (10,2) (10,10)

    // 不能卡住 主线程
    // 开启子线程 去执行 这个任务  这样就可以不卡死主线程了
    new std::thread(&FinalPosWindow2::sweepV, this);

}

void FinalPosWindow2::sweepV() {
    for (int i = 2; i < 11; ++i) {
        // (i,2) (i,10)
        this->moveToPoint(i, 2);
        this->moveToPoint(i, 10);
    }

}


void FinalPosWindow2::moveToPoint(double dstX, double dstY) {
    geometry_msgs::Twist twist;
    std_msgs::Float64 f64;

    double time = 5; // 运动耗时
    double angularTime = time / 12; // 转弯耗时,这里假设是运动时间的1/12
    double hz = 60;
    ros::Rate rate(hz);

    double distance, theta_displacement;
    double pvLinearX = 0; // 初始速度应为0
    double pvAngularZ = 0; // 初始角速度
    double svLinearX, errLinearX; // err = sv - pv
    double svAngularZ, errAngularZ; // err = sv - pv

    double totalErrLinearX = 0;
    double totalErrAngularZ = 0;
    double lastErrLinearX = 0;
    double lastErrAngularZ = 0;

    double kp = this->kpEditLine->text().toDouble();
    double ki = this->kiEditLine->text().toDouble();
    double kd = this->kdEditLine->text().toDouble();
    while (true) {

        f64.data = pvLinearX;
        this->plotVelPublisher.publish(f64);

        twist.linear.x = pvLinearX;
        twist.angular.z = pvAngularZ;
        this->velPublisher.publish(twist);


        rate.sleep();

        distance = this->calcDistance(dstX, dstY);
        if (distance < 0.05)
            break;
        theta_displacement = this->calcThetaDisplacement(dstX,dstY);
        pvAngularZ = theta_displacement / angularTime;

        time -= 1 / hz;

        svLinearX = distance / time; // 每次 sv 都会变
        errLinearX = svLinearX - pvLinearX;
        totalErrLinearX += errLinearX;

        pvLinearX += kp * errLinearX + ki * totalErrLinearX + kd * (errLinearX - lastErrLinearX);

        lastErrLinearX = errLinearX;


    }

    // 最后1s 也不让 它走了
    twist.linear.x = 0;
    twist.angular.z = 0;
    this->velPublisher.publish(twist);


}

// 小乌龟 到达 目标点
void FinalPosWindow2::sendMsgEvt() {

    // 开启子线程 去执行 这个任务  这样就可以不卡死主线程了
    new std::thread(&FinalPosWindow2::moveTurtle, this);

}
/*
// 单独 P  算法
void FinalPosWindow2::moveTurtle() {
    geometry_msgs::Twist twist;
    std_msgs::Float64 f64;

    // dest pose
    double dstX = this->finalPosX->text().toDouble();
    double dstY = this->finalPosY->text().toDouble();

    double time = 5; // 耗时
    double hz = 60;
    ros::Rate rate(hz);

    double distance = this->calcDistance(dstX, dstY);
    double pvLinearX = 0; // 初始速度应为0
    double svLinearX, errLinearX; // err = sv - pv

    double kp = this->kpEditLine->text().toDouble();
    // 速度增量 和 distance 可能会出 bug,解决方法:1 up hz 2 up err
    while (true) { // 0.01 误差值 有点小

        f64.data = pvLinearX;
        this->plotVelPublisher.publish(f64);

        twist.linear.x = pvLinearX;
        twist.angular.z = 0;
        this->velPublisher.publish(twist);

        rate.sleep();

        distance = this->calcDistance(dstX, dstY);
        if(distance <  0.1)
            break;

        time -= 1 / hz;
        svLinearX = distance / time; // 每次 sv 都会变
        errLinearX = svLinearX - pvLinearX;
        pvLinearX += kp * errLinearX;
    }

    // 最后1s 也不让 它走了
    twist.linear.x = 0;
    twist.angular.z = 0;
    this->velPublisher.publish(twist);

}
*/

/*
// 单独 I算法
void FinalPosWindow2::moveTurtle() {
    geometry_msgs::Twist twist;
    std_msgs::Float64 f64;

    // dest pose
    double dstX = this->finalPosX->text().toDouble();
    double dstY = this->finalPosY->text().toDouble();

    double time = 5; // 耗时
    double hz = 60;
    ros::Rate rate(hz);

    double distance = this->calcDistance(dstX, dstY);
    double pvLinearX = 0; // 初始速度应为0
    double svLinearX, errLinearX; // err = sv - pv
    double totalErrLinearX = 0;

    double ki = this->kiEditLine->text().toDouble();
    // 速度增量 和 distance 可能会出 bug,解决方法:1 up hz 2 up err
    while (true) { // 0.01 误差值 有点小

        f64.data = pvLinearX;
        this->plotVelPublisher.publish(f64);

        twist.linear.x = pvLinearX;
        twist.angular.z = 0;
        this->velPublisher.publish(twist);

        rate.sleep();

        distance = this->calcDistance(dstX, dstY);
        if (distance < 0.1)
            break;

        time -= 1 / hz;
        svLinearX = distance / time; // 每次 sv 都会变
        errLinearX = svLinearX - pvLinearX;
        totalErrLinearX += errLinearX;
        pvLinearX += ki * totalErrLinearX;
    }

    // 最后1s 也不让 它走了
    twist.linear.x = 0;
    twist.angular.z = 0;
    this->velPublisher.publish(twist);

}
*/

/*
// 单独D  算法,调试时kd 取1
void FinalPosWindow2::moveTurtle() {
    geometry_msgs::Twist twist;
    std_msgs::Float64 f64;

    // dest pose
    double dstX = this->finalPosX->text().toDouble();
    double dstY = this->finalPosY->text().toDouble();

    double time = 5; // 耗时
    double hz = 60;
    ros::Rate rate(hz);

    double distance = this->calcDistance(dstX, dstY);
    double pvLinearX = 0; // 初始速度应为0
    double svLinearX, errLinearX; // err = sv - pv
    double lastErrLinearX = 0;

    double kd = this->kdEditLine->text().toDouble();
    while (true) {

        f64.data = pvLinearX;
        this->plotVelPublisher.publish(f64);

        twist.linear.x = pvLinearX;
        twist.angular.z = 0;
        this->velPublisher.publish(twist);

        rate.sleep();

        distance = this->calcDistance(dstX, dstY);
        if(distance < 0.3)
            break;

        time -= 1 / hz;
        svLinearX = distance / time; // 每次 sv 都会变
        errLinearX = svLinearX - pvLinearX;

        pvLinearX += kd * (errLinearX - lastErrLinearX);
        lastErrLinearX = errLinearX;
    }

    // 最后1s 也不让 它走了
    twist.linear.x = 0;
    twist.angular.z = 0;
    this->velPublisher.publish(twist);

}
*/

// 一般情况下，PI PD PID 结合，一般不会单独使用 I 和 D算法
/*
 * 从下面的代码中提取出 moveToPoint() 方法
void FinalPosWindow2::moveTurtle() {
    geometry_msgs::Twist twist;
    std_msgs::Float64 f64;

    // dest pose
    double dstX = this->finalPosX->text().toDouble();
    double dstY = this->finalPosY->text().toDouble();

    double time = 5; // 运动耗时
    double angularTime = time / 10; // 转弯耗时,这里假设是运动时间的1/10
    double hz = 60;
    ros::Rate rate(hz);

    double distance, theta_displacement;
    double pvLinearX = 0; // 初始速度应为0
    double pvAngularZ = 0; // 初始角速度
    double svLinearX, errLinearX; // err = sv - pv
    double svAngularZ, errAngularZ; // err = sv - pv

    double totalErrLinearX = 0;
    double totalErrAngularZ = 0;
    double lastErrLinearX = 0;
    double lastErrAngularZ = 0;

    double kp = this->kpEditLine->text().toDouble();
    double ki = this->kiEditLine->text().toDouble();
    double kd = this->kdEditLine->text().toDouble();
    while (true) {

        f64.data = pvLinearX;
        this->plotVelPublisher.publish(f64);

        twist.linear.x = pvLinearX;
        twist.angular.z = pvAngularZ;
        this->velPublisher.publish(twist);

        rate.sleep();

        distance = this->calcDistance(dstX, dstY);
        theta_displacement = this->calcThetaDisplacement(dstX, dstY);
        pvAngularZ = theta_displacement / angularTime;
        if (distance < 0.01)
            break;

        time -= 1 / hz;

        svLinearX = distance / time; // 每次 sv 都会变
        errLinearX = svLinearX - pvLinearX;
        totalErrLinearX += errLinearX;

        pvLinearX += kp * errLinearX + ki * totalErrLinearX + kd * (errLinearX - lastErrLinearX);

        lastErrLinearX = errLinearX;
    }

    // 最后1s 也不让 它走了
    twist.linear.x = 0;
    twist.angular.z = 0;
    this->velPublisher.publish(twist);

}

 */
void FinalPosWindow2::moveTurtle() {

    // dest pose
    double dstX = this->finalPosX->text().toDouble();
    double dstY = this->finalPosY->text().toDouble();

    this->moveToPoint(dstX, dstY);
}

void FinalPosWindow2::poseCallback(const turtlesim::Pose::ConstPtr &msg) {
    this->curX = msg->x;
    this->curY = msg->y;
    this->curTheta = msg->theta;
}

double FinalPosWindow2::calcDistance(double dstX, double dstY) {
    double deltaX = dstX - this->curX;
    double deltaY = dstY - this->curY;

    return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

double FinalPosWindow2::calcThetaDisplacement(double dstX, double dstY) {
    double deltaX = dstX - this->curX;
    double deltaY = dstY - this->curY;

    /* atan 的取值是 (-90，90)      atan2 是基于 atan 的！
    // atan2 取值 (-180,180]   curTheta取值(-180,180]
    // theta 取值就是: atan2 - curTheta 的取值就是(-360,360) 这时小乌龟就犹豫不决有多个值可选,如何解决?方法是降区间
    double theta = atan2(deltaY, deltaX) - this->curTheta;
    */

    // 我自己的解决方案： 降低区间为 (-180,180]
//    double targetTheta = atan2(deltaY, deltaX);
//    if (abs(targetTheta - curTheta) > M_PI) { // 肯定是 异号的,即条件是：异号且差值大于PI
//        if (targetTheta < 0)
//            targetTheta += 2 * M_PI;
//        else
//            curTheta += 2 * M_PI;
//    }
//    return targetTheta - curTheta;

    // 老师的 方案 : 降低区间为 （-180,180]  NB!
    double theta = atan2(deltaY, deltaX) - this->curTheta;
    if (theta > M_PI) // 右侧 边界
        theta -= 2 * M_PI; // 181 -> -179   182 -> -178 ...
    else if (theta <= -M_PI)// 左侧边界
        theta += 2 * M_PI; // -180 -> 180  -181 -> 179
    return theta;
}


void FinalPosWindow2::onUpdate() {

    ros::spinOnce(); // ros 回调
    this->update(); // qt 回调

    if (!ros::ok()) { // 如果当前 node 挂了,就是ctrl+c 了
        this->close(); // qt 也要关闭
    }
}



