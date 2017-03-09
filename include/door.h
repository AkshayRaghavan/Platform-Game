#ifndef DOOR_H
#define DOOR_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>

/*!
 * \brief The area which marks the end point of the game
 * The Door is an object, which when a player touches, the player completes the game
 */

class Door : public QGraphicsRectItem
{
    /*!
     * \brief x coordinate
     */
    qreal x;

    /*!
     * \brief y coordinate
     */
    qreal y;

    /*!
     * \brief width
     */
    qreal w;

    /*!
     * \brief height
     */
    qreal h;

    /*!
     * \brief the QGraphicsRectItem to store the way the door is drawn
     */
    QGraphicsRectItem *r;
public:

    /*!
     * \brief Constructor
     * \param x x coordinate
     * \param y y coordinate
     * \param w width
     * \param h height
     * \param scene the scene in which the door is drawn
     */
    Door(qreal x, qreal y, qreal w, qreal h, QGraphicsScene *scene);
};

#endif // DOOR_H
