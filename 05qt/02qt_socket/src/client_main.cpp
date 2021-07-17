//
// Created by zcb on 7/8/21.
//

#include <iostream>
#include <QApplication>
#include "Client.h"

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    Client *client = new Client();
    client->show();

    return app.exec();
}



