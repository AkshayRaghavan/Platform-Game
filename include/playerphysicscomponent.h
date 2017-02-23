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
private:
    int velocity,acceleration;
    int newx,newy;
    std::vector<std::vector<Tile*>> Tilesmap;
    QGraphicsScene * scene;
    int width_of_tile,height_of_tile,screenWidth,screenHeight;
    int curJumpCount,maxJumpCount;
public:
    //The constructor will initialize the parameters
    PlayerPhysicsComponent(std::vector<std::vector<Tile*>> &,int,int,int,int,QGraphicsScene*);
    void update(GameObject &ob);
};

#endif // PLAYERPHYSICSCOMPONENT_H
