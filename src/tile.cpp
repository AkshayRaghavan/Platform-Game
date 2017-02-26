#include "tile.h"

Tile::Tile(int column , int row , int width , int height , bool is_obstacle)
{
    this->columnPosition = column;
    this->widthOfTile = width;
    this->heightOfTile = height;
    this->rowPosition = row;
    this->isObstacle = is_obstacle;
}

bool Tile::getIsObstacle()
{
    return this->isObstacle;
}

int Tile::getWidthOfTile()
{
    return this->widthOfTile;
}

int Tile::getHeightOfTile()
{
    return this->heightOfTile;
}


