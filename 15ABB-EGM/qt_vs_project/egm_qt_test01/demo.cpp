#include "demo.h"

#include "qdebug.h"
#include <windows.h>

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	server = new QUdpSocket(this);
	server->bind(QHostAddress("127.0.0.1"), 6510);
	connect(server, &QUdpSocket::readyRead, this, &Demo::connWithRemote);
	connect(ui.drawBoard, &MyDrawBoard::currentPoint, this, &Demo::on_drawBoard_currentPoint);
}

Demo::~Demo()
{
	delete server;
}

void Demo::displayRobotMessage(EgmRobot * pRobotMessage)
{
	if (pRobotMessage->has_header() && 
		pRobotMessage->header().has_seqno() && 
		pRobotMessage->header().has_tm() && 
		pRobotMessage->header().has_mtype() && 
		pRobotMessage->has_feedback() && 
		pRobotMessage->feedback().has_joints() &&
		pRobotMessage->feedback().has_cartesian() &&
		pRobotMessage->feedback().has_time()
		)
	{



		QString header = QString::asprintf(" SeqNo=%d Tm=%u Type=%d\n", pRobotMessage->header().seqno(), pRobotMessage->header().tm(), pRobotMessage->header().mtype());

		auto joints = pRobotMessage->feedback().joints().joints();
		QString sJoints = QString::asprintf(" J1:%f J2:%f J3:%f J4:%f J5:%f J6:%f\n", joints[0], joints[1], joints[2], joints[3], joints[4], joints[5]);

		auto pos = pRobotMessage->feedback().cartesian().pos();
		auto orient = pRobotMessage->feedback().cartesian().orient();
		auto euler = pRobotMessage->feedback().cartesian().euler();
		QString sPos = QString::asprintf(" X:%f Y:%f Z:%f\n", pos.x(), pos.y(), pos.z());
		QString sOrient = QString::asprintf(" q1:%f q2:%f q3:%f q4:%f\n", orient.u0(),orient.u1(),orient.u2(),orient.u3());
		QString sEuler = QString::asprintf(" Rx:%f Ry:%f Rz:%f\n", euler.x(), euler.y(), euler.z());

		// ui joint 
		ui.j1->setText(QString::asprintf(" %f", joints[0]));
		ui.j2->setText(QString::asprintf(" %f", joints[1]));
		ui.j3->setText(QString::asprintf(" %f", joints[2]));
		ui.j4->setText(QString::asprintf(" %f", joints[3]));
		ui.j5->setText(QString::asprintf(" %f", joints[4]));
		ui.j6->setText(QString::asprintf(" %f", joints[5]));

		// ui pos 
		ui.x->setText(QString::asprintf(" %f", pos.x()));
		ui.y->setText(QString::asprintf(" %f", pos.y()));
		ui.z->setText(QString::asprintf(" %f", pos.z()));

		// ui orient
		ui.q1->setText(QString::asprintf(" %f", orient.u0()));
		ui.q2->setText(QString::asprintf(" %f", orient.u1()));
		ui.q3->setText(QString::asprintf(" %f", orient.u2()));
		ui.q4->setText(QString::asprintf(" %f", orient.u3()));

		// ui euler 
		ui.rx->setText(QString::asprintf(" %f", euler.x()));
		ui.ry->setText(QString::asprintf(" %f", euler.y()));
		ui.rz->setText(QString::asprintf(" %f", euler.z()));


		ui.plainTextEdit->setPlainText(header+ sJoints+sPos+sEuler+sOrient);
	}
	else
	{
		ui.plainTextEdit->setPlainText("No Data From Robot");
	}
}

void Demo::createSensorMessage(EgmSensor* pSensorMessage,double x,double y)
{
	static unsigned int sequenceNumber = 1;
	EgmHeader* header = new EgmHeader();
	header->set_mtype(EgmHeader_MessageType_MSGTYPE_CORRECTION);
	header->set_seqno(sequenceNumber++);
	header->set_tm(GetTickCount());

	pSensorMessage->set_allocated_header(header);

	EgmCartesian *pc = new EgmCartesian();
	pc->set_x(x);
	pc->set_y(y);
	pc->set_z(320);


	EgmQuaternion *pq = new EgmQuaternion();
	pq->set_u0(0.0);
	pq->set_u1(0.0);
	pq->set_u2(1.0);
	pq->set_u3(0.0);

	EgmPose *pcartesian = new EgmPose();
	pcartesian->set_allocated_orient(pq);
	pcartesian->set_allocated_pos(pc);

	EgmPlanned *planned = new EgmPlanned();
	planned->set_allocated_cartesian(pcartesian);

	pSensorMessage->set_allocated_planned(planned);
}


void Demo::connWithRemote()
{

	while (server->hasPendingDatagrams())
	{
		QByteArray ba;
		ba.resize(server->pendingDatagramSize());
		int n = server->readDatagram(ba.data(), ba.size(),&robIp,&robPort);

		EgmRobot *pRobotMessage = new EgmRobot();
		pRobotMessage->ParseFromArray(ba.data(), n);
		displayRobotMessage(pRobotMessage);
		delete pRobotMessage;
	}

}

void Demo::on_drawBoard_currentPoint(QPoint pt)
{
	//	x 200 -> 500
	//	y - 150 - 150
	//	z 320
	//  ui 界面 x: 0->400 y: 0->400 
	double x = pt.x() / 400.0 * 300 + 200;
	double y = pt.y() / 400.0 * 300 - 150;

	EgmSensor *pSensorMessage = new EgmSensor();
	createSensorMessage(pSensorMessage,x,y);

	std::string msg;
	pSensorMessage->SerializeToString(&msg);
	qDebug() << QString::fromStdString(msg);
	server->writeDatagram(QByteArray::fromStdString(msg), robIp, robPort);

	delete pSensorMessage;

}
