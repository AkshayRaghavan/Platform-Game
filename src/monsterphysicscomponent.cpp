#include "monsterphysicscomponent.h"
#include <QGraphicsItem>
#include <QDebug>

MonsterPhysicsComponent::MonsterPhysicsComponent(std::vector<std::vector<Tile*>> &Tilesmap, qreal theight, qreal twidth, qreal sheight, qreal swidth, int fraction_of_speed)
{
    velocity = 1;
    this->tilesMap = Tilesmap;
    width_of_tile = twidth;
    height_of_tile = theight;
    screenHeight = sheight;
    screenWidth = swidth;
    maxSpeedFraction = fraction_of_speed;
    curSpeedFraction = fraction_of_speed;
}

void MonsterPhysicsComponent::update(GameObject &gameObject)
{
    curSpeedFraction--;
    if(curSpeedFraction < 0)
    {
        curSpeedFraction = maxSpeedFraction;
    }
    std::vector<qreal> positionAndSize = gameObject.graphicsComponent->getSizePositionOfObject();
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
    QPointF current_point(positionAndSize[0],positionAndSize[1]);
    QPointF going_to_point = current_point;
    qreal player_width = positionAndSize[2];
    qreal player_height = positionAndSize[3];
    enumerator::State current_player_state = gameObject.state->type();
    if(current_player_state == enumerator::State::MOVING_RIGHT)
    {
        going_to_point.setX(going_to_point.x() + width_of_tile);
    }
    else if(current_player_state == enumerator::State::MOVING_LEFT)
    {
        going_to_point.setX(going_to_point.x() - width_of_tile);
    }
    if(testPositionForPlayer(going_to_point,player_width,player_height) && !curSpeedFraction)
    {
        gameObject.graphicsComponent->setPos(going_to_point);
        current_point.setX(going_to_point.x());
    }
    going_to_point = current_point;
    int going_to_tile_row = going_to_point.y()/height_of_tile;
    int going_to_tile_column = going_to_point.x()/width_of_tile;
    if(inRange(QPointF(going_to_point.x(),going_to_point.y()+height_of_tile)) && !(tilesMap[going_to_tile_row+1][going_to_tile_column])->getIsObstacle())
    {
 //       qDebug() << "inrange is true";
        going_to_point.setY(going_to_point.y()+height_of_tile);
    }
    if(testPositionForPlayer(going_to_point,player_width,player_height))
    {
     //   qDebug() << "monster can now move";
        gameObject.graphicsComponent->setPos(going_to_point);
    }
}



