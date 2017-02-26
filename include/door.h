#ifndef DOOR_H
#define DOOR_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>

class Door : public QGraphicsRectItem
{
    qreal x;
    qreal y;
    qreal w;
    qreal h;
    QGraphicsRectItem *r;
public:
    Door(qreal x, qreal y, qreal w, qreal h, QGraphicsScene *scene);
};

#endif // DOOR_H
