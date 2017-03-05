#include "timer.h"
#include <QDebug>

Timer::Timer(int total_time_available, int milliseconds_per_frame)
{
    secondsLeft = total_time_available/1000;
    total_time_available %= 1000;
    millisecondsLeft = total_time_available;
    millisecondsPerFrame = milliseconds_per_frame;
    isLeft = true;
    qDebug() << "s: " << secondsLeft;
    qDebug() << "ms: " << millisecondsLeft;
}

void Timer::update()
{
    //qDebug() << "game over" << secondsLeft << " " << millisecondsLeft << " " << millisecondsPerFrame;
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
        //qDebug() << "game over" << secondsLeft << " " << millisecondsLeft << " " << millisecondsPerFrame;
        millisecondsLeft = 0;
        isLeft = false;
    }
    std::string time_string = getTimeLeft();
    //this->setPlainText(time_string.c_str());
}

std::string Timer::getTimeLeft()
{
     std::string time_string = std::to_string(secondsLeft) + " : " + std::to_string(millisecondsLeft);
     return time_string;
}

std::string Timer::setTimeLeft(int timeLeft)
{
     secondsLeft = timeLeft/1000;
     millisecondsLeft = timeLeft%1000;
     this->setPlainText(getTimeLeft().c_str());
}


int Timer::getTimeLeftInMilliSeconds()
{

     return (secondsLeft*1000 + millisecondsLeft);
}


bool Timer::isTimeLeft()
{
    return isLeft;
}
