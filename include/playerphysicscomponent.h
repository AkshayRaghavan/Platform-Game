#ifndef PLAYERPHYSICSCOMPONENT_H
#define PLAYERPHYSICSCOMPONENT_H

#include "physicscomponent.h"
#include "playergraphicscomponent.h"
#include "enumerator.h"
#include "state.h"
#include "jumpingstate.h"
#include "gameobject.h"
#include "tile.h"
#include <QGraphicsScene>

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
    //The constructor will initialize the parameters
    PlayerPhysicsComponent(std::vector< std::vector<Tile*> > &,int,int,int,int,QGraphicsScene*);
    void update(GameObject &);
};

#endif // PLAYERPHYSICSCOMPONENT_H
