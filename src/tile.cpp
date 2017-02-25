#include "tile.h"

Tile::Tile(QGraphicsScene* scene , int column , int row , int width , int height , bool is_obstacle, bool is_dangerous)
{
    QPen outlinePen;
    this->columnPosition = column;
    this->widthOfTile = width;
    this->heightOfTile = height;
    this->rowPosition = row;

    outlinePen.setColor((is_obstacle==true)? Qt::red : Qt::blue);
    outlinePen.setWidth(1);
    this->r = scene->addRect(column , row , width , height , outlinePen);
    this->isObstacle = is_obstacle;
    this->isDangerous = is_dangerous;
}

QGraphicsRectItem* Tile::getR()
{
    return this->r;
}

bool Tile::getIsObstacle()
{
    return this->isObstacle;
}

bool Tile::getIsDangerous()
{
    return this->isDangerous;
}

int Tile::getWidthOfTile()
{
    return this->widthOfTile;
}

int Tile::getHeightOfTile()
{
    return this->heightOfTile;
}


