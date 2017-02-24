#include "physicscomponent.h"
#include "playerphysicscomponent.h"
#include <typeinfo>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "gem.h"
#include "deadleft.h"
#include "deadright.h"
#include <stdlib.h>
#include "graphicscomponent.h"
#include "gameobject.h"
#include "isjumping.h"
#include "isnotjumping.h"
#include "diamond.h"
#include <QPainter>

bool PhysicsComponent::inRange(QPointF input_point)
{
    qreal x = input_point.x();
    qreal y = input_point.y();
    int number_of_rows_in_map = tilesMap.size();
    int number_of_columns_in_map;
    if(number_of_rows_in_map > 0)
    {
        number_of_columns_in_map = tilesMap[0].size();
    }
    else
    {
        number_of_columns_in_map = 0;
    }
    int tile_row_coordinate = y/height_of_tile;
    int tile_column_coordinate = x/width_of_tile;
    if(x < 0 || y < 0 || tile_row_coordinate >= number_of_rows_in_map || tile_column_coordinate >= number_of_columns_in_map)
    {
        return false;
    }
    if((tilesMap[tile_row_coordinate][tile_column_coordinate])->getIsObstacle())
    {
        return false;
    }
    return true;
}

bool PhysicsComponent::testPoint(QPointF input_point)
{
    qreal x = input_point.x();
    qreal y = input_point.y();
    int number_of_rows_in_map = tilesMap.size();
    int number_of_columns_in_map;
    if(number_of_rows_in_map > 0)
    {
        number_of_columns_in_map = tilesMap[0].size();
    }
    else
    {
        number_of_columns_in_map = 0;
    }
    int tile_row_coordinate = y/height_of_tile;
    int tile_column_coordinate = x/width_of_tile;
    if(x < 0 || y < 0 || tile_row_coordinate >= number_of_rows_in_map || tile_column_coordinate >= number_of_columns_in_map)
    {
        return false;
    }
    if((tilesMap[tile_row_coordinate][tile_column_coordinate])->getIsObstacle())
    {
        return false;
    }
    return true;
}

bool PhysicsComponent::testPositionForPlayer(QPointF input_point, qreal player_width, qreal player_height)
{
    qreal x = input_point.x();
    qreal y = input_point.y();
    int number_of_rows_in_map = tilesMap.size();
    int number_of_columns_in_map;
    if(number_of_rows_in_map > 0)
    {
        number_of_columns_in_map = tilesMap[0].size();
    }
    else
    {
        number_of_columns_in_map = 0;
    }
    for(int i = x; i < x + player_width; i+= width_of_tile)
    {
        for(int j = y; j < y + player_height; j += height_of_tile)
        {
            if(!testPoint(QPointF(i,j)))
            {
 //               qDebug() << "failing because of point " << i << ", " << j;
                return false;
            }
        }
    }
    return true;
}
