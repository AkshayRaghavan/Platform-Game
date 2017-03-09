#include "timer.h"
#include <QDebug>

Timer::Timer(int total_time_available, int milliseconds_per_frame)
{
    secondsLeft = total_time_available/1000;
    total_time_available %= 1000;
    millisecondsLeft = total_time_available;
    millisecondsPerFrame = milliseconds_per_frame;
    isLeft = true;
}

void Timer::update()
{
    if(millisecondsLeft >= millisecondsPerFrame)
    {
        millisecondsLeft -= millisecondsPerFrame;
    }
    else if(secondsLeft > 0)
    {
        secondsLeft--;
        millisecondsLeft += 1000;
        millisecondsLeft -= millisecondsPerFrame;
    }
    else
    {
        millisecondsLeft = 0;
        isLeft = false;
    }
}

void Timer::updateTimerOnScreen()
{
    QString time_string = QString("Time : ") + QString::number(secondsLeft) + " : " + QString::number(millisecondsLeft);
    this->setHtml(time_string);
}

void Timer::setTimeLeft(int timeLeft)
{
     secondsLeft = timeLeft/1000;
     millisecondsLeft = timeLeft%1000;
}

int Timer::getTimeLeftInMilliSeconds()
{
     return (secondsLeft*1000 + millisecondsLeft);
}

bool Timer::isTimeLeft()
{
    return isLeft;
}
