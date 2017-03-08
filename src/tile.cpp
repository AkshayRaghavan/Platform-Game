#include "tile.h"

Tile::Tile(QGraphicsScene * scene , qreal column , qreal row , qreal width , qreal height , bool is_obstacle)
{
    this->columnPosition = column;
    this->widthOfTile = width;
    this->heightOfTile = height;
    this->rowPosition = row;

    /* To Generate Tile On Screen (For Debugging Purposes)
     * QPen outlinePen;
     * outlinePen.setColor((is_obstacle==true)? Qt::red : Qt::blue);
     * outlinePen.setWidth(1);
     * scene->addRect(column , row , width , height , outlinePen);
    */

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

