//
// Created by zcb on 7/8/21.
//

#include "Server.h"
#include <iostream>

using namespace std;

Server::Server(QWidget *parent) : QWidget(parent) {

    // 1 setup ui
    setUI();

    // 2 init server socket
    initServerSocket();

    // 3 当点击发送时 发送消息
    connect(sendBtn,&QPushButton::clicked,[=](){
        QString msg = this->sendTextEdit->toPlainText();
        this->socket->write(msg.toUtf8().data());
    });
}

Server::~Server() {

}


void Server::setUI() {
    this->setWindowTitle("服务端");
    this->setFixedSize(600, 600);

    // layout
    // 两个输入输出框
    this->vLayout = new QVBoxLayout(this);
    this->recvTextEdit = new QTextEdit();
    this->sendTextEdit = new QTextEdit();

    recvTextEdit->setEnabled(false);// 不让用户编辑

    this->vLayout->addWidget(recvTextEdit);
    this->vLayout->addWidget(sendTextEdit);

    // 两个按钮
    this->hLayout = new QHBoxLayout();
    this->sendBtn = new QPushButton("发送");
    this->closeBtn = new QPushButton("关闭");
    hLayout->addWidget(sendBtn);
    hLayout->addWidget(closeBtn);

    this->vLayout->addLayout(hLayout);// 将两个按钮所在的h_layout 加入到 v_layout中
}

void Server::initServerSocket() {

    this->server = new QTcpServer(this);
    server->listen(QHostAddress::AnyIPv4, 8888);

    connect(server, &QTcpServer::newConnection, this, &Server::client_cb); //当有客户端连接过来的时候,会触发 client_cb
}

void Server::client_cb() {
    // 有新的客户端连接进来了
    this->socket = server->nextPendingConnection(); // 此 socket是专门负责 某个客户端的fd,当客户端断开的时候要关闭此文件描述符
    string client_ip = socket->peerAddress().toString().toStdString();
    //cout << client_ip << endl;
    int client_port = socket->peerPort();
    recvTextEdit->append(QString::fromStdString("客户端[ip,port]" + client_ip + " " + to_string(client_port) + " 连接成功"));

    // 监听此客户端是否发消息过来
    connect(socket, &QTcpSocket::readyRead, this, &Server::client_msg_cb);
}

void Server::client_msg_cb() {
    // 客户端发来了消息
    string data = this->socket->readAll().toStdString();
    recvTextEdit->append(QString::fromStdString(data));
}

