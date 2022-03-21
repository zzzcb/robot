#pragma once

#include <QtWidgets/QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkDatagram>

#include "ui_demo.h"

#include "egm.pb.h"
using namespace abb::egm;


class Demo : public QMainWindow
{
    Q_OBJECT

public:
	Demo(QWidget *parent = Q_NULLPTR);
	~Demo();

private:
    Ui::DemoClass ui;

	QUdpSocket* server;
	QHostAddress robIp;
	quint16 robPort;
	
	void displayRobotMessage(EgmRobot * pRobotMessage);
	void createSensorMessage(EgmSensor* pSensorMessage, double x, double y);

private slots:
	void connWithRemote();
	void on_drawBoard_currentPoint(QPoint pt);
};
