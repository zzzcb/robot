//
// Created by zcb on 7/17/21.
//

#include "Client.h"

Client::Client(QWidget *parent) : QWidget(parent) {
    // set up ui
    setUI();

    initClientSocket();

    // 当点击 连接 的时候获取ip 和 端口
    connect(this->connectBtn,&QPushButton::clicked,[=](){ // 值传递
        QString ip = ipEdit->text();
        int port = portEdit->text().toInt();
        socket->connectToHost(ip,port);
    });

    // 当 点击 发送的时候,向服务端发送内容
    connect(this->sendBtn,&QPushButton::clicked,[=](){// 值传递
        QString msg = this->sendTextEdit->toPlainText();
        socket->write(msg.toUtf8().data());
    });
    // 当接受到消息时 展示出来
    connect(socket,&QTcpSocket::readyRead,[=](){
        QByteArray data = socket->readAll();
        this->recvTextEdit->append(QString(data));
    });

}

void Client::setUI() {
    this->setWindowTitle("客户端");
    this->setFixedSize(600, 600);

    // layout
    this->vLayout = new QVBoxLayout(this);

    // 1 连接服务器布局
    this->hLayoutTop = new QHBoxLayout();

    this->formLayout = new QFormLayout();
    this->ipEdit = new QLineEdit("127.0.0.1");
    this->portEdit = new QLineEdit("8888");
    this->formLayout->addRow("服务器IP",ipEdit);
    this->formLayout->addRow("服务器port",portEdit);

    hLayoutTop->addLayout(formLayout);
    this->connectBtn = new QPushButton("连接");
    hLayoutTop->addWidget(connectBtn);

    vLayout->addLayout(hLayoutTop);// 将hLayoutTop 加入到 整体的 vLayout 中

    // 2 两个输入输出框
    this->recvTextEdit = new QTextEdit();
    this->sendTextEdit = new QTextEdit();

    recvTextEdit->setEnabled(false);// 不让用户编辑

    this->vLayout->addWidget(recvTextEdit);
    this->vLayout->addWidget(sendTextEdit);

    // 3 两个按钮
    this->hLayoutBottom = new QHBoxLayout();
    this->sendBtn = new QPushButton("发送");
    this->closeBtn = new QPushButton("关闭");
    hLayoutBottom->addWidget(sendBtn);
    hLayoutBottom->addWidget(closeBtn);

    this->vLayout->addLayout(hLayoutBottom);// 将两个按钮所在的h_layout 加入到 v_layout中

}

Client::~Client() {

}

void Client::initClientSocket() {

    this->socket = new QTcpSocket(this);

}

