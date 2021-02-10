#include "QtReactionTest.h"

QtReactionTest::QtReactionTest(QWidget *parent)
    : QWidget(parent)
{
	setFixedSize(500, 500);
	setAutoFillBackground(true);

	state = Idle;

	text = new QLabel("Click to start");
	text->setFont(QFont("Arial", 25, QFont::Normal));
	changeBackColor(QColor(Qt::blue));

	QHBoxLayout* layout = new QHBoxLayout;
	layout->setAlignment(Qt::AlignCenter);
	layout->addWidget(text);
	setLayout(layout);
}

void QtReactionTest::mousePressEvent(QMouseEvent* e)
{
	switch (state)
	{
	case Idle:
	{
		state = Early;
		text->setText("");
		changeBackColor(QColor(Qt::yellow));

		alarm = new Alarm(this);
		connect(alarm, &Alarm::onTime, this, &QtReactionTest::onTimeSignal);
		connect(this, SIGNAL(stopTimer()), alarm, SLOT(stopTimer()));

		alarm->start();

		break;
	}
	case Early:
	{
		state = Over;
		text->setText("You are too early!");
		changeBackColor(QColor(Qt::gray));

		emit stopTimer();
		if (alarm && alarm->isRunning())
			alarm->wait();

		break;
	}
	case OnTime:
	{
		reactionTime = clock() - reactionTime;
		QString res = QString("Your result is: %1").arg(((float)reactionTime) / CLOCKS_PER_SEC);

		state = Over;
		text->setText(res);
		changeBackColor(QColor(Qt::green));

		break;
	}
	case Over:
	{
		state = Idle;
		text->setText("Click to start");
		changeBackColor(QColor(Qt::blue));

		break;
	}
	}
}

void QtReactionTest::changeBackColor(QColor color)
{
	QPalette pal;
	pal.setBrush(backgroundRole(), QBrush(color));
	setPalette(pal);
}

void QtReactionTest::onTimeSignal()
{
	state = OnTime;
	changeBackColor(QColor(Qt::red));
	reactionTime = clock();
}