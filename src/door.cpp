#include "door.h"
#include <QPen>

Door::Door(qreal x, qreal y, qreal w, qreal h, QGraphicsScene * scene)
{

    QPen pen;
    pen.setColor(Qt::transparent);
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->r = scene->addRect(x,y,w,h,pen);
}
