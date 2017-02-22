#include "playerphysicscomponent.h"
extern tile Tilesmap;
extern int score;
PlayerPhysicsComponent::PlayerPhysicsComponent()
{
    velocity = 0;
    acceleration = 1;
}

void PlayerPhysicsComponent::update(GameObject & ob)
{
    int newx,newy;
    newx=ob.graphicscomponent->x();
    newy=ob.graphicscomponent->y();
    int state_index = static_cast<int> ((ob.state)->type());
    int jumping_state_index = static_cast<int> ((ob.jumpingState)->type());
    newy-=width_of_tile;

    if(state_index == 0)
    {
        newx+=width_of_tile;
    }
    else if(state_index == 1)
    {
        newx-=width_of_tile;
    }

    if(jumping_state_index == 1)
    {
        newy=ob.graphicscomponent->y()-((0<velocity)-(velocity<0))*height_of_tile;
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
        ob.graphicscomponent->offset(newx,newy);
        if((screenTilesObject[newy/height_of_tile][newx/width_of_tile])->ispoint) {
            (screenTilesObject[newy/height_of_tile][newx/width_of_tile])->change_point_type();
            score++;
        }
    }


}
