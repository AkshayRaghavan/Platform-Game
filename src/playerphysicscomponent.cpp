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

PlayerPhysicsComponent::PlayerPhysicsComponent(std::vector<std::vector<Tile*> > &Tilesmap, int theight, int twidth, int sheight, int swidth, QGraphicsScene * scene)
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

/*void PlayerPhysicsComponent::update(GameObject & ob)
{
    int newx,newy,height,width;
    std::vector<qreal> details(4);
    details = ob.graphicsComponent->getSizePositionOfObject();
    newx = details[0];
    newy = details[1];
    width = details[2];
    height = details[3];*/

    //qDebug() <<"tata "<<newx << " , "<<newy<<" , "<<width<<" , "<<height;
/*    enumerator::State state_index =  ((ob.state)->type());
    enumerator::JumpingState jumping_state_index =  ((ob.jumpingState)->type());*/

    /*if(Tilesmap[newy/height_of_tile + 1][newx/width_of_tile]->getIsObstacle())
    {
        ob.setState(new IsJumping);
    }*/

    /*if(!((Tilesmap[newy/height_of_tile][newx/width_of_tile])->getIsObstacle() || (Tilesmap[newy/height_of_tile][(newx+width)/width_of_tile])->getIsObstacle() || (Tilesmap[(newy + height)/height_of_tile][newx/width_of_tile])->getIsObstacle() || (Tilesmap[(newy + height)/height_of_tile][(newx+width)/width_of_tile])->getIsObstacle() ))
    {
        newy+=height_of_tile;
        ob.graphicsComponent->setPos(newx,newy);
    }*/
    //qDebug() <<"physics "<<newy;
 /*   if(state_index == enumerator::State::MOVING_RIGHT)
    {
        newx+=width_of_tile;
    }
    else if(state_index == enumerator::State::MOVING_LEFT)
    {
        newx-=width_of_tile;
    }

    if(!((Tilesmap[newy/height_of_tile][newx/width_of_tile])->getIsObstacle() || (Tilesmap[newy/height_of_tile][(newx+width)/width_of_tile])->getIsObstacle() ))
    {
        if(newx<=0)
        {
            newx=0;
        }
        else if ( newx + width > screenWidth-width_of_tile )
        {
            newx= screenWidth - width_of_tile - width;
        }
        ob.graphicsComponent->setPos(newx,newy);
    }

    if(jumping_state_index == enumerator::JumpingState::IS_JUMPING)
    {
        if(curJumpCount <= maxJumpCount){
            newy = newy - 2*(height_of_tile);
            curJumpCount++;
        }
        if((newy + height_of_tile < screenHeight) && (newx < screenWidth) && (((Tilesmap[(newy+height+height_of_tile)/height_of_tile][newx/width_of_tile])->getIsObstacle()) || ((Tilesmap[(newy+height+height_of_tile)/height_of_tile][(newx+width)/width_of_tile])->getIsObstacle()))) {
            ob.setJumpingState(new IsNotJumping);
            curJumpCount = 0;
        }
    }

    if (newy <= 0)
    {
        newy=0;
    }
    else if ( newy + height > screenHeight-height_of_tile)
    {
       newy= screenHeight-height_of_tile - height;
    }*/


    //qDebug() << Tilesmap[newy/height_of_tile][newx/width_of_tile];
   // qDebug() << newy << newx;

   // qDebug() << newy/height_of_tile << newx/width_of_tile;
   // qDebug() << Tilesmap[newy/height_of_tile][newx/width_of_tile]->getIsObstacle();
  /*  bool canMove = true;
    for(int i = newy; i < newy + height; i++)
    {
        for(int j = newx; j < newx + width; j++)
        {
            if((i + height_of_tile  < screenHeight) && (j + width_of_tile  < screenWidth) && (tilesMap[i/height_of_tile][j/width_of_tile])->getIsObstacle())
            {
//                qDebug() << "made false, tried to go to "<<newx<<" "<<newy;
                canMove = false;
            }
            else
            {
//                qDebug() << "made false, tried to go to "<<newx<<" "<<newy;
                canMove = false;
            }
        }
    }*/

 //   if(!((Tilesmap[newy/height_of_tile][newx/width_of_tile])->getIsObstacle() || (Tilesmap[newy/height_of_tile][(newx+width)/width_of_tile])->getIsObstacle() || (Tilesmap[(newy + height)/height_of_tile][newx/width_of_tile])->getIsObstacle() || (Tilesmap[(newy + height)/height_of_tile][(newx+width)/width_of_tile])->getIsObstacle() ))
    //if(canMove)
//    {
      //  qDebug() <<"harsh "<<newy;
 //       ob.graphicsComponent->setPos(newx,newy);
        /*QList<QGraphicsItem *> colliding_items = ob.graphicsComponent->collidingItems();
        for(int i = 0, n = colliding_items.size();i<n;i++) {
            if(typeid(*(colliding_items[i])) == typeid(Gem)){
                ob.setScore(ob.getScore()+1);
                scene->removeItem(colliding_items[i]);
                delete colliding_items[i];
            }
            if(typeid(*(colliding_items[i])) == typeid(GraphicsComponent)){
                GraphicsComponent * temp;
                temp = (GraphicsComponent *)colliding_items[i];
                if(((*temp).getIsMonster()) == true) {
                    // getismonster() is a member of graphics component to check moster
                    if(state_index == enumerator::State::MOVING_RIGHT)
                    {
                        ob.setState(new DeadRight);
                    }
                    else
                    {
                        ob.setState(new DeadLeft);
                    }
                }
            }
        }*/
/*    }
newy+=height_of_tile;
    if(!((Tilesmap[newy/height_of_tile][newx/width_of_tile])->getIsObstacle() || (Tilesmap[newy/height_of_tile][(newx+width)/width_of_tile])->getIsObstacle() || (Tilesmap[(newy + height)/height_of_tile][newx/width_of_tile])->getIsObstacle() || (Tilesmap[(newy + height)/height_of_tile][(newx+width)/width_of_tile])->getIsObstacle() ))
    {

        ob.graphicsComponent->setPos(newx,newy);
    }


}*/

bool PlayerPhysicsComponent::inRange(QPointF input_point)
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

bool PlayerPhysicsComponent::testPoint(QPointF input_point)
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

bool PlayerPhysicsComponent::testPositionForPlayer(QPointF input_point, qreal player_width, qreal player_height)
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
        gameObject.graphicsComponent->setPos(going_to_point);
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
 //       qDebug() << "inrange is true";
        going_to_point.setY(going_to_point.y()+height_of_tile);
    }
    if(testPositionForPlayer(going_to_point,player_width,player_height))
    {
        gameObject.graphicsComponent->setPos(going_to_point);
    }
    else
    {
   //     qDebug() << "cannot allow going to " << going_to_tile_row << ", " << going_to_tile_column;
    }
    if(current_player_state == enumerator::State::DEAD_LEFT || current_player_state == enumerator::State::DEAD_RIGHT)
    {
        return;
    }
    QList<QGraphicsItem *> colliding_items = gameObject.graphicsComponent->collidingItems();
    qDebug() << "colliding with " << colliding_items.size() << " items";
    for(int i = 0; i < colliding_items.size(); i++)
    {
  //      qDebug() << "in for";
        if(typeid(*(colliding_items[i])) == typeid(Diamond))
        {
            qDebug() << "found a gem";
            gameObject.setScore(gameObject.getScore()+1);
            scene->removeItem(colliding_items[i]);
            delete colliding_items[i];
        }
        else if(typeid(*(colliding_items[i])) == typeid(GraphicsComponent))
        {
            GraphicsComponent * temp;
            temp = static_cast<GraphicsComponent*>(colliding_items[i]);
            if(((*temp).getIsMonster()) == true)
            {
                // getismonster() is a member of graphics component to check monster
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


