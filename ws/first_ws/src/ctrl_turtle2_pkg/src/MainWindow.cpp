//
// Created by zcb on 2021/4/10.
//

#include "MainWindow.h"
#include <std_srvs/Empty.h>
#include <turtlesim/Spawn.h>
#include <turtlesim/Kill.h>
#include <turtlesim/SetPen.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/TeleportRelative.h>

MainWindow::MainWindow(ros::NodeHandle *node, QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("小乌龟控制");
    this->setFixedSize(500, 300);

    // 关于 QTimer
    this->updateTimer = new QTimer(this);
    this->updateTimer->setInterval(16); // 1000 / 60fps = 16 ms
    QTimer::connect(this->updateTimer, &QTimer::timeout, this, &MainWindow::onUpdate);
    this->updateTimer->start();

    this->node = node;

    // ui 布局
    this->setUI();

    // connect to slot func
    this->connectSlot();

}

MainWindow::~MainWindow() {

}

void MainWindow::onUpdate() {
    // ros 回调
    ros::spinOnce();
    // qt 回调
    this->update();

    if (!ros::ok()) {
        this->close();
    }
}


void MainWindow::setUI() {
    this->ly = new QFormLayout(this);

    clearBtn = new QPushButton("清理画布");
    this->ly->addRow(clearBtn);

    resetBtn = new QPushButton("重置");
    this->ly->addRow(resetBtn);

    QHBoxLayout *h_ly_spawn = new QHBoxLayout();
    spawnX = new QLineEdit();
    spawnX->setPlaceholderText("X坐标");
    spawnY = new QLineEdit();
    spawnY->setPlaceholderText("Y坐标");
    spawnTheta = new QLineEdit();
    spawnTheta->setPlaceholderText("角度");
    spawnName = new QLineEdit();
    spawnName->setPlaceholderText("名字");
    spawnBtn = new QPushButton("创建小乌龟");
    h_ly_spawn->addWidget(spawnX);
    h_ly_spawn->addWidget(spawnY);
    h_ly_spawn->addWidget(spawnTheta);
    h_ly_spawn->addWidget(spawnName);
    h_ly_spawn->addWidget(spawnBtn);
    this->ly->addRow(h_ly_spawn);

    QHBoxLayout *h_ly_kill = new QHBoxLayout();
    killName = new QLineEdit();
    killName->setPlaceholderText("名字");
    killBtn = new QPushButton("杀死小乌龟");
    h_ly_kill->addWidget(killName);
    h_ly_kill->addWidget(killBtn);
    this->ly->addRow(h_ly_kill);

    QHBoxLayout *h_ly_set_pen = new QHBoxLayout();
    setPenName = new QLineEdit();
    setPenName->setPlaceholderText("名字");
    setPenR = new QLineEdit();
    setPenR->setPlaceholderText("红");
    setPenG = new QLineEdit();
    setPenG->setPlaceholderText("绿");
    setPenB = new QLineEdit();
    setPenB->setPlaceholderText("蓝");
    setPenWidth = new QLineEdit();
    setPenWidth->setPlaceholderText("粗细");
    setPenOff = new QCheckBox("关闭");
    setPenBtn = new QPushButton("设置画笔");
    h_ly_set_pen->addWidget(setPenName);
    h_ly_set_pen->addWidget(setPenR);
    h_ly_set_pen->addWidget(setPenG);
    h_ly_set_pen->addWidget(setPenB);
    h_ly_set_pen->addWidget(setPenWidth);
    h_ly_set_pen->addWidget(setPenOff);
    h_ly_set_pen->addWidget(setPenBtn);
    this->ly->addRow(h_ly_set_pen);


    QHBoxLayout *h_ly_abs = new QHBoxLayout();
    abs_name = new QLineEdit();
    abs_name->setPlaceholderText("名字");
    abs_x = new QLineEdit();
    abs_x->setPlaceholderText("X坐标");
    abs_y = new QLineEdit();
    abs_y->setPlaceholderText("Y坐标");
    abs_theta = new QLineEdit();
    abs_theta->setPlaceholderText("角度");
    teleportAbsoluteBtn = new QPushButton("设置绝对位置");
    h_ly_abs->addWidget(abs_name);
    h_ly_abs->addWidget(abs_x);
    h_ly_abs->addWidget(abs_y);
    h_ly_abs->addWidget(abs_theta);
    h_ly_abs->addWidget(teleportAbsoluteBtn);
    this->ly->addRow(h_ly_abs);


    QHBoxLayout *h_ly_rel = new QHBoxLayout();
    rel_name = new QLineEdit();
    rel_name->setPlaceholderText("名字");
    rel_linear = new QLineEdit();
    rel_linear->setPlaceholderText("线速度");
    rel_angular = new QLineEdit();
    rel_angular->setPlaceholderText("角速度");
    teleportRelativeBtn = new QPushButton("设置相对位置");
    h_ly_rel->addWidget(rel_name);
    h_ly_rel->addWidget(rel_linear);
    h_ly_rel->addWidget(rel_angular);
    h_ly_rel->addWidget(teleportRelativeBtn);
    this->ly->addRow(h_ly_rel);

}


void MainWindow::connectSlot() {
    QPushButton::connect(this->clearBtn, &QPushButton::clicked, this, &MainWindow::clickClear);
    QPushButton::connect(this->resetBtn, &QPushButton::clicked, this, &MainWindow::clickReset);
    QPushButton::connect(this->spawnBtn, &QPushButton::clicked, this, &MainWindow::clickSpawn);
    QPushButton::connect(this->killBtn, &QPushButton::clicked, this, &MainWindow::clickKill);
    QPushButton::connect(this->setPenBtn, &QPushButton::clicked, this, &MainWindow::clickSetPen);
    QPushButton::connect(this->teleportAbsoluteBtn, &QPushButton::clicked, this, &MainWindow::clickAbs);
    QPushButton::connect(this->teleportRelativeBtn, &QPushButton::clicked, this, &MainWindow::clickRel);
}

void MainWindow::clickClear() {

    ros::ServiceClient clear_client = node->serviceClient<std_srvs::Empty>("/clear");
    std_srvs::Empty service;
    clear_client.call(service);

    clear_client.shutdown(); // 关闭这个临时客户端
}

void MainWindow::clickReset() {

    ros::ServiceClient reset_client = node->serviceClient<std_srvs::Empty>("/reset");
    std_srvs::Empty service;
    reset_client.call(service);

    reset_client.shutdown();
}

void MainWindow::clickSpawn() {
    ros::ServiceClient spawn_client = node->serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn service;
    service.request.x = this->spawnX->text().toFloat();
    service.request.y = this->spawnY->text().toFloat();
    service.request.theta = this->spawnTheta->text().toFloat() * M_PI / 180;
    service.request.name = this->spawnName->text().toStdString();

    spawn_client.call(service);

    spawn_client.shutdown();
}

void MainWindow::clickKill() {
    ros::ServiceClient kill_client = node->serviceClient<turtlesim::Kill>("/kill");
    turtlesim::Kill service;
    service.request.name = this->killName->text().toStdString();

    kill_client.call(service);

    kill_client.shutdown();
}

void MainWindow::clickSetPen() {
    std::string nodeName = this->setPenName->text().toStdString();
    ros::ServiceClient set_pen_client = node->serviceClient<turtlesim::SetPen>("/" + nodeName + "/set_pen");
    turtlesim::SetPen service;
    service.request.r = this->setPenR->text().toUInt();
    service.request.g = this->setPenG->text().toUInt();
    service.request.b = this->setPenB->text().toUInt();
    service.request.width = this->setPenWidth->text().toUInt();
    service.request.off = this->setPenOff->isChecked();

    set_pen_client.call(service);
    set_pen_client.shutdown();
}

void MainWindow::clickAbs() {
    std::string nodeName = this->abs_name->text().toStdString();
    ros::ServiceClient abs_client = node->serviceClient<turtlesim::TeleportAbsolute>(
            "/" + nodeName + "/teleport_absolute");
    turtlesim::TeleportAbsolute service;
    service.request.x = this->abs_x->text().toFloat();
    service.request.y = this->abs_y->text().toFloat();
    service.request.theta = this->abs_theta->text().toFloat() * M_PI / 180;

    abs_client.call(service);
    abs_client.shutdown();
}

void MainWindow::clickRel() {
    std::string nodeName = this->rel_name->text().toStdString();
    ros::ServiceClient rel_client = node->serviceClient<turtlesim::TeleportRelative>(
            "/" + nodeName + "/teleport_relative");
    turtlesim::TeleportRelative service;
    service.request.linear = this->rel_linear->text().toFloat();
    service.request.angular = this->rel_angular->text().toFloat() * M_PI / 180;
    rel_client.call(service);

    rel_client.shutdown();
}
