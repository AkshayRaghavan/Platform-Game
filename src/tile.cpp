#include "tile.h"
#include <QPen>
#include <QFont>
#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

tile::tile(QGraphicsScene* scene , int left , int top , int width , int height , bool isObstacle, bool ispoint) {
    QPen outlinePen;
    this->left=left;
    this->width=width;
    this->height=height;
    this->top=top;
    if(isObstacle == true) {
        outlinePen.setColor(Qt::red);
    }
    else if(ispoint == true) {
        outlinePen.setColor(Qt::blue);
    }
    else
        outlinePen.setColor(Qt::transparent);
    //QPen outlinePen((isObstacle == true)? Qt::red : Qt::transparent);
    outlinePen.setWidth((isObstacle == true)? 3 : 2);
    this->r = scene->addRect(left , top , width , height , outlinePen );
    this->isObstacle = isObstacle;
    this->ispoint = ispoint;
    this->scene = scene;
}

void tile::change_point_type()
{
    this->ispoint = false;
    scene->removeItem(this->r);
    QPen outlinePen;
    outlinePen.setColor(Qt::transparent);
    outlinePen.setWidth((isObstacle == true)? 3 : 2);
    this->r = scene->addRect(left , top , width , height , outlinePen );

}
