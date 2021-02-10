#pragma once

#include <QtWidgets>

#include "StateEnum.h"
#include "Alarm.h"

class QtReactionTest : public QWidget
{
    Q_OBJECT

public:
    QtReactionTest(QWidget *parent = Q_NULLPTR);

protected:
	void mousePressEvent(QMouseEvent* e) override;

private:
	QLabel* text;
	StateEnum state;
	QPointer<Alarm> alarm;
	clock_t reactionTime;

	void changeBackColor(QColor color);

private slots:
	void onTimeSignal();

signals:
	void stopTimer();

};
