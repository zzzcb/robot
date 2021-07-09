//
// Created by zcb on 7/8/21.
//

#include "ZcbWindow.h"
#include <iostream>

ZcbWindow::ZcbWindow(QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("我是zcb窗口");
    this->setFixedSize(640, 480);

    // layout
    this->formlayout = new QFormLayout(this);

    this->btn = new QPushButton("btn");
    this->btn2 = new QPushButton("btn2");
    this->formlayout->addRow("点我console打印hello", this->btn);
    this->formlayout->addRow("发射自定义的信号 zcbed", this->btn2);

    // 连接 信号 和 槽
    connect(this->btn, &QPushButton::clicked, this, &ZcbWindow::clickbtn);
    connect(this->btn2, &QPushButton::clicked, this, &ZcbWindow::fashexinhao);

    // 连接 自定义 信号 和 槽,这个自定义信号 需要点击btn2 来触发
    connect(this, &ZcbWindow::zcbed, this, &ZcbWindow::clickbtn);
}

ZcbWindow::~ZcbWindow() {

}

void ZcbWindow::clickbtn() {
    std::cout << "hello" << this->cnt++ << std::endl;
}

void ZcbWindow::fashexinhao() {
    emit this->zcbed();
}

