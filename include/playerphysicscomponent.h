#ifndef PLAYERPHYSICSCOMPONENT_H
#define PLAYERPHYSICSCOMPONENT_H

#include "physicscomponent.h"
#include "playergraphicscomponent.h"
#include "enumerator.h"
#include "state.h"
#include "jumpingstate.h"
#include "gameobject.h"
#include "tile.h"

class PlayerPhysicsComponent : public PhysicsComponent
{
private:
    int velocity,acceleration;
    int newx(),newy();
public:
    //The constructor will initialize the parameters
    PlayerPhysicsComponent();
    void update(GameObject &ob);
};

#endif // PLAYERPHYSICSCOMPONENT_H
