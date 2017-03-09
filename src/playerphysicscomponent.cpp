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
#include <QMediaPlayer>
#include <QFileInfo>

PlayerPhysicsComponent::PlayerPhysicsComponent(std::vector<std::vector<Tile*> > &Tilesmap, qreal theight, qreal twidth, qreal sheight, qreal swidth, QGraphicsScene * scene)
{
    this->tilesMap = Tilesmap;
    width_of_tile = twidth;
    height_of_tile = theight;
    screenHeight = sheight;
    screenWidth = swidth;
    this->scene = scene;
    curJumpCount = 0;
    maxJumpCount = 20;
}
void PlayerPhysicsComponent::update(GameObject &gameObject)
{
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
    enumerator::JumpingState current_player_jumping_state = gameObject.jumpingState->type();
    if(current_player_state == enumerator::State::MOVING_RIGHT)
    {
        going_to_point.setX(going_to_point.x() + width_of_tile);
    }
    else if(current_player_state == enumerator::State::MOVING_LEFT)
    {
        going_to_point.setX(going_to_point.x() - width_of_tile);
    }

    if(testPositionForPlayer(going_to_point,player_width,player_height))
    {
        gameObject.setPosXY(going_to_point);
        current_point.setX(going_to_point.x());
    }
    going_to_point = current_point;
    if(current_player_jumping_state == enumerator::JumpingState::IS_JUMPING)
    {

        if(current_player_state == enumerator::State::DEAD_LEFT || current_player_state == enumerator::State::DEAD_RIGHT)
        {
            curJumpCount = maxJumpCount;
        }
        else if(curJumpCount < maxJumpCount)
        {
            curJumpCount++;
            going_to_point.setY(going_to_point.y() - 2*height_of_tile);
        }
        else if(!testPositionForPlayer(QPointF(going_to_point.x(),going_to_point.y()+height_of_tile),player_width,player_height))
        {
            qDebug() << "set to not jumping";
            gameObject.setJumpingState(new IsNotJumping);
            curJumpCount = 0;
        }
    }
    else if(current_player_jumping_state == enumerator::JumpingState::IS_NOT_JUMPING)
    {
        if(testPositionForPlayer(QPointF(going_to_point.x(),going_to_point.y()+height_of_tile),player_width,player_height))
        {
            gameObject.setJumpingState(new IsJumping(gameObject));
            curJumpCount = maxJumpCount;
        }
    }
    int going_to_tile_row = going_to_point.y()/height_of_tile;
    int going_to_tile_column = going_to_point.x()/width_of_tile;
    if(inRange(QPointF(going_to_point.x(),going_to_point.y()+height_of_tile)) && !(tilesMap[going_to_tile_row+1][going_to_tile_column])->getIsObstacle())
    {
        going_to_point.setY(going_to_point.y()+height_of_tile);
    }
    if(testPositionForPlayer(going_to_point,player_width,player_height))
    {
        gameObject.setPosXY(going_to_point);
    }
    else
    {
    }
    if(current_player_state == enumerator::State::DEAD_LEFT || current_player_state == enumerator::State::DEAD_RIGHT)
    {
        return;
    }
    QList<QGraphicsItem *> colliding_items = gameObject.graphicsComponent->collidingItems();
    for(int i = 0; i < colliding_items.size(); i++)
    {
        if(typeid(*(colliding_items[i])) == typeid(Diamond) && (static_cast<Gem*>(colliding_items[i]))->getIsOnScreen())
        {
            qDebug() << gameObject.getScore();
            gameObject.setScore(gameObject.getScore() + (static_cast<Gem*>(colliding_items[i]))->getPointValue());
            (static_cast<Gem*>(colliding_items[i]))->setIsOnScreen(false);
        }
        else if(typeid(*(colliding_items[i])) == typeid(QGraphicsRectItem))
        {
            gameObject.setState(new StopRight);
            gameObject.setJumpingState(new IsNotJumping);
            gameObject.setAcceptingInput(false);
        }
        else if(typeid(*(colliding_items[i])) == typeid(PlayerGraphicsComponent) || typeid(*(colliding_items[i])) == typeid(FireGraphicsComponent))
        {
            GraphicsComponent * temp;
            temp = static_cast<GraphicsComponent*>(colliding_items[i]);
            if(((*temp).getIsDangerous()) == true)
            {
                gameObject.setIsDead(true);
                if(current_player_state == enumerator::State::MOVING_RIGHT || current_player_state == enumerator::State::STOP_RIGHT)
                {
                    gameObject.setState(new DeadRight);
                }
                else
                {
                    gameObject.setState(new DeadLeft);
                }
            }
        }
    }
}
