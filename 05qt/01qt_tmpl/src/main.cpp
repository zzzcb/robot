//
// Created by zcb on 7/8/21.
//

#include <iostream>
#include <QApplication>
#include "ZcbWindow.h"

int main(int argc,char** argv){

    QApplication app(argc,argv);

    ZcbWindow* zcb = new ZcbWindow();
    zcb->show();

    return app.exec();
}








