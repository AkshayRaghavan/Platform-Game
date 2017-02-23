#include "monsterphysicscomponent.h"
#include <QGraphicsItem>

extern tile ***Tilesmap;

MonsterPhysicsComponent::MonsterPhysicsComponent() {
    velocity = 1;
}

void MonsterPhysicsComponent::update(GameObject & ob)
{
    int newx,newy;
    newx=ob.graphicsComponent->x();
    newy=ob.graphicsComponent->y();
    enumerator::State state_index =  ((ob.state)->type());
    enumerator::JumpingState jumping_state_index =  ((ob.jumpingState)->type());
    newy-=width_of_tile;

    if(state_index == enumerator::State::MOVING_RIGHT)
    {
        newx+=width_of_tile;
    }
    else if(state_index == enumerator::State::MOVING_LEFT)
    {
        newx-=width_of_tile;
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
    if(!(Tilesmap[newy/height_of_tile][newx/width_of_tile])->isObstacle)
    {
        ob.graphicsComponent->setOffset(newx,newy);
    }

}
