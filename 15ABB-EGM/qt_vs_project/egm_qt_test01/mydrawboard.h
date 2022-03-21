#pragma once

#include <QFrame>
#include <QMouseEvent>

class MyDrawBoard : public QFrame
{
	Q_OBJECT

public:
	MyDrawBoard(QWidget *parent);
	~MyDrawBoard();

private:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

	QVector<QPoint> mvPoint = {};
signals:
	void currentPoint(QPoint pt);
};
