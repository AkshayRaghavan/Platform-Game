#include "tile.h"

Tile::Tile(QGraphicsScene* scene , int left , int top , int width , int height , bool is_obstacle)
{
    QPen outlinePen;
    this->left_position = left;
    this->widthOfTile = width;
    this->heightOfTile = height;
    this->top_position = top;
    outlinePen.setColor(Qt::transparent);
    outlinePen.setWidth(1);
    this->r = scene->addRect(left , top , width , height , outlinePen);
    this->isObstacle = is_obstacle;
}

QGraphicsRectItem* Tile::getR()
{
    return this->r;
}

bool Tile::getIsObstacle()
{
    return isObstacle;
}
