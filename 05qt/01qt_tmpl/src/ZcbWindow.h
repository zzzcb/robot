//
// Created by zcb on 7/8/21.
//

#ifndef QT_ZCBWINDOW_H
#define QT_ZCBWINDOW_H

#include <QWidget>
#include <QFormLayout>
#include <QPushButton>


class ZcbWindow : public QWidget {
Q_OBJECT    // 使用信号的使用需要添加 ,这里有个巨坑，此时，.h 和 .cpp 应该放在一个目录，不然会报 vtable 错误，所以这个文件不能放在include目录中了，需要拉回来
public:
    ZcbWindow(QWidget *parent = nullptr);

    ~ZcbWindow();


private:
    QFormLayout *formlayout;
    QPushButton *btn;
    QPushButton *btn2;

    int cnt = 0;

signals:
    void zcbed(); // 自定义信号 //信号要和槽匹配,信号的参数个数要大于槽

private: // slot
    void clickbtn();
    void fashexinhao();
};


#endif //QT_ZCBWINDOW_H
