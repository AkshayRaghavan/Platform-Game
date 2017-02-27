#ifndef TIMER_H
#define TIMER_H

#include <QGraphicsTextItem>
#include <string>

class Timer : public QGraphicsTextItem
{
private:
    int secondsLeft;
    int millisecondsLeft;
    int millisecondsPerFrame;
    bool isLeft;
public:
    Timer(int, int);
    virtual ~Timer() {}
    bool isTimeLeft();
    std::string getTimeLeft();
    void update();

};

#endif // TIMER_H