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

PlayerPhysicsComponent::PlayerPhysicsComponent(Tile *** Tilesmap, int theight, int twidth, int sheight, int swidth, QGraphicsScene * scene)
{
    this->Tilesmap = Tilesmap;
    width_of_tile = twidth;
    height_of_tile = theight;
    screenHeight = sheight;
    screenWidth = swidth;
    this->scene = scene;
    curJumpCount = 0;
    maxJumpCount = 5;
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
    enumerator::State state_index =  ((ob.state)->type());
    enumerator::JumpingState jumping_state_index =  ((ob.jumpingState)->type());
    newy+=height_of_tile;

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
        if((Tilesmap[(newy+height_of_tile)/height_of_tile][newx/width_of_tile])->getIsObstacle()) {
            ob.setJumpingState(new IsNotJumping);
        }
    }

    if(newx<=0)
    {
        newx=0;
    }
    else if (newx > screenWidth-width_of_tile)
    {
        newx= screenWidth - width_of_tile;
    }

    if (newy <= 0)
    {
        newy=0;
    }
    else if ( newy > screenHeight-height_of_tile)
    {
       newy= screenHeight-height_of_tile;
    }

    if(!(Tilesmap[newy/height_of_tile][newx/width_of_tile])->getIsObstacle())
    {
        ob.graphicsComponent->setOffset(newx,newy);
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
                if(((*temp).getIsMonster()) == true ){
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
