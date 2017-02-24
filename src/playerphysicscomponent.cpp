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

PlayerPhysicsComponent::PlayerPhysicsComponent(std::vector<std::vector<Tile*> > &Tilesmap, int theight, int twidth, int sheight, int swidth, QGraphicsScene * scene)
{

    this->Tilesmap = Tilesmap;
    width_of_tile = twidth;
    height_of_tile = theight;
    screenHeight = sheight;
    screenWidth = swidth;
    this->scene = scene;
    curJumpCount = 0;
    maxJumpCount = 20;
    qDebug() <<"physics "<<twidth << " , " << theight;

}

void PlayerPhysicsComponent::update(GameObject & ob)
{
    int newx,newy,height,width;
    std::vector<qreal> details(4);
    details = ob.graphicsComponent->getSizePositionOfObject();
    newx = details[0];
    newy = details[1];
    width = details[2];
    height = details[3];

    //qDebug() <<"tata "<<newx << " , "<<newy<<" , "<<width<<" , "<<height;
    enumerator::State state_index =  ((ob.state)->type());
    enumerator::JumpingState jumping_state_index =  ((ob.jumpingState)->type());
    newy += height_of_tile;
    //qDebug() <<"physics "<<newy;
    if(state_index == enumerator::State::MOVING_RIGHT)
    {
        newx+=width_of_tile;
    }
    else if(state_index == enumerator::State::MOVING_LEFT)
    {
        newx-=width_of_tile;
    }

    if(jumping_state_index == enumerator::JumpingState::IS_JUMPING)
    {
        if(curJumpCount <= maxJumpCount){
            newy = newy - 2*(height_of_tile);
            curJumpCount++;
        }
        if((newy + height + height_of_tile < screenHeight) && (newx + width < screenWidth) && (((Tilesmap[(newy+height+height_of_tile)/height_of_tile][newx/width_of_tile])->getIsObstacle()) || ((Tilesmap[(newy+height+height_of_tile)/height_of_tile][(newx+width)/width_of_tile])->getIsObstacle()))) {
            ob.setJumpingState(new IsNotJumping);
            curJumpCount = 0;
        }
    }

    if(newx<=0)
    {
        newx=0;
    }
    else if ( newx + width > screenWidth-width_of_tile )
    {
        newx= screenWidth - width_of_tile - width;
    }

    if (newy <= 0)
    {
        newy=0;
    }
    else if ( newy + height > screenHeight-height_of_tile)
    {
       newy= screenHeight-height_of_tile - height;
    }


    //qDebug() << Tilesmap[newy/height_of_tile][newx/width_of_tile];
   // qDebug() << newy << newx;

   // qDebug() << newy/height_of_tile << newx/width_of_tile;
   // qDebug() << Tilesmap[newy/height_of_tile][newx/width_of_tile]->getIsObstacle();
    bool canMove = true;
    for(int i = newy; i < newy + height; i++)
    {
        for(int j = newx; j < newx + width; j++)
        {
            if((i + height_of_tile  < screenHeight) && (j + width_of_tile  < screenWidth) && (Tilesmap[i/height_of_tile][j/width_of_tile])->getIsObstacle())
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
    }
   if(!((Tilesmap[newy/height_of_tile][newx/width_of_tile])->getIsObstacle() || (Tilesmap[newy/height_of_tile][(newx+width)/width_of_tile])->getIsObstacle() ))
    // if(canMove)
    {
      //  qDebug() <<"harsh "<<newy;
        ob.graphicsComponent->setPos(newx,newy);
        QList<QGraphicsItem *> colliding_items = ob.graphicsComponent->collidingItems();
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
        }
    }


}
