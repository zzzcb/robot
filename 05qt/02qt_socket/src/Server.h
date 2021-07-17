//
// Created by zcb on 7/8/21.
//

#ifndef QT_SERVER_H
#define QT_SERVER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>

#include <QHBoxLayout>
#include <QPushButton>

#include <QTcpServer>
#include <QTcpSocket>


class Server : public QWidget {
Q_OBJECT    // 使用自定义信号的使用需要添加 ,这里有个巨坑，此时，.h 和 .cpp 应该放在一个目录，不然会报 vtable 错误，所以这个文件不能放在include目录中了，需要拉回来
public:
    Server(QWidget *parent = nullptr);

    ~Server();
private:
    //ui
    QVBoxLayout *vLayout;
    QTextEdit* recvTextEdit,* sendTextEdit;

    QHBoxLayout *hLayout;
    QPushButton* sendBtn,* closeBtn;

    void setUI();

    //socket
    QTcpServer* server;
    QTcpSocket* socket;

    void initServerSocket();

private: // slot
    void client_cb(); // 客户端连接上server时 触发
    void client_msg_cb(); // 客户端发送消息时 触发

};

#endif //QT_SERVER_H
