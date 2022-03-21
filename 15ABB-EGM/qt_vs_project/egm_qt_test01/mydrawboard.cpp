#include "mydrawboard.h"
#include <qdebug.h>
#include <QPainter>

MyDrawBoard::MyDrawBoard(QWidget *parent)
	: QFrame(parent)
{
	this->setAttribute(Qt::WA_StyledBackground);	// 父亲的样式不影响本体
	this->setStyleSheet("background-color:#fff");
	this->setFrameShape(QFrame::Box);
}

MyDrawBoard::~MyDrawBoard()
{
}

void MyDrawBoard::mousePressEvent(QMouseEvent *event)
{
	if (event->x() < 0 || event->y() < 0 || event->x() > 400 || event->y() > 400)
		return;
	mvPoint.push_back(QPoint(event->x(),event->y()));
}
/**
	机器人运动范围
		x 200 -> 500
		y -150 - 150
		z 320
*/
void MyDrawBoard::mouseMoveEvent(QMouseEvent *event)
{
	if (event->x() < 0 || event->y() < 0 || event->x() > 400 || event->y() > 400)
		return;

	mvPoint.push_back(QPoint(event->x(),event->y()));
	update();

	// 将当前点位发射出去 
	emit currentPoint(event->pos());
}

void MyDrawBoard::mouseReleaseEvent(QMouseEvent *event)
{
	mvPoint.clear();
	update();
}

void MyDrawBoard::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QPen pen(QColor("red"));
	pen.setWidth(4);
	painter.setPen(pen);

	painter.drawPoints(QPolygon(mvPoint));
}

