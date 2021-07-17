//
// Created by zcb on 7/17/21.
//

#ifndef QT_CLIENT_H
#define QT_CLIENT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>

#include <QTcpSocket>

class Client : public QWidget {
Q_OBJECT
public:
    Client(QWidget *parent = nullptr);

    ~Client();

private:
    //ui
    QVBoxLayout *vLayout;
    QTextEdit *recvTextEdit, *sendTextEdit;

    QHBoxLayout *hLayoutTop,*hLayoutBottom;
    QPushButton *sendBtn, *closeBtn;

    QFormLayout *formLayout;
    QLineEdit* ipEdit,*portEdit;
    QPushButton* connectBtn;

    void setUI();

    //socket
    QTcpSocket* socket;


private: // slot
    void initClientSocket();
};

#endif //QT_CLIENT_H
