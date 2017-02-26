#include "tile.h"

Tile::Tile(QGraphicsScene* scene , qreal column , qreal row , qreal width , qreal height , bool is_obstacle)
{
    QPen outlinePen;
    this->columnPosition = column;
    this->widthOfTile = width;
    this->heightOfTile = height;
    this->rowPosition = row;

    /*outlinePen.setColor((is_obstacle==true)? Qt::red : Qt::blue);
    outlinePen.setWidth(1);
    this->r = scene->addRect(column , row , width , height , outlinePen); */
    this->isObstacle = is_obstacle;
}

QGraphicsRectItem* Tile::getR()
{
    return this->r;
}

bool Tile::getIsObstacle()
{
    return this->isObstacle;
}

qreal Tile::getWidthOfTile()
{
    return this->widthOfTile;
}

qreal Tile::getHeightOfTile()
{
    return this->heightOfTile;
}

