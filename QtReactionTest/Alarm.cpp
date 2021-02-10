#include "Alarm.h"

Alarm::Alarm(QObject* parent)
	:QThread(parent)
{
	gen.seed(QDateTime::currentMSecsSinceEpoch());
	mSec = 500 + gen() % 3501;
	stop = false;

	connect(this, SIGNAL(finished()), SLOT(deleteLater()));
}

void Alarm::run()
{
	while (!stop)
	{
		msleep(100);
		
		mSec -= 100;

		if (mSec < 0)
		{
			emit onTime();
			break;
		}
	}
}

void Alarm::stopTimer()
{
	stop = true;
}