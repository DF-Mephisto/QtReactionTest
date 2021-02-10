#pragma once

#include <QtCore>
#include <random>

using namespace std;

class Alarm : public QThread
{
	Q_OBJECT

public:
	Alarm(QObject* parent = 0);

protected:
	void run() override;

private:
	mt19937 gen;
	int mSec;
	bool stop;

private slots:
	void stopTimer();

signals:
	void onTime();

};

