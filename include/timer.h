#ifndef TIMER_H
#define TIMER_H

#include <QGraphicsTextItem>
#include <string>

/*!
 * \brief Class That maintains the timer
 */

class Timer : public QGraphicsTextItem
{
private:
    /*!
     * \brief Time left in seconds
     */
    int secondsLeft;
    /*!
     * \brief Time left in mili-seconds
     */
    int millisecondsLeft;
    /*!
     * \brief Mili-Seconds to advance per Frame
     */
    int millisecondsPerFrame;
    /*!
     * \brief Used to check if time is over
     */
    bool isLeft;
public:
    /*!
     * \brief Constructor for Timer Class
     * \param total_time_available Total Time to countdown
     * \param milliseconds_per_frame Mili-Seconds to advance per frame
     */
    Timer(int total_time_available, int milliseconds_per_frame);
    /*!
     * \brief Destructor for Timer Class
     */
    virtual ~Timer() {}
    /*!
     * \brief To check if time is left
     * \return Returns whether time is left or not
     */
    bool isTimeLeft();
    /*!
     * \brief Function to update Timer
     */
    void updateTimerOnScreen();
    /*!
     * \brief Function to update Time Left
     */
    void setTimeLeft(int);
    /*!
     * \brief Function to get time Left converted in Mili-Seconds
     * \return
     */
    int getTimeLeftInMilliSeconds();
    /*!
     * \brief function to update the Timer
     */
    void update();

};

#endif // TIMER_H
