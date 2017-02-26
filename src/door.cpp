#include "door.h"

Door::Door(qreal x, qreal y, qreal w, qreal h, QGraphicsScene * scene)
{
    this->setRect(x,y,w,h);
    scene -> addItem(this);
}
