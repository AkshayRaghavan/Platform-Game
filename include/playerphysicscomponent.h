#ifndef PLAYERPHYSICSCOMPONENT_H
#define PLAYERPHYSICSCOMPONENT_H

#include "physicscomponent.h"
#include "playergraphicscomponent.h"
#include "firegraphicscomponent.h"
#include "enumerator.h"
#include "state.h"
#include "jumpingstate.h"
#include "gameobject.h"
#include "tile.h"
#include "door.h"
#include "stopleft.h"
#include "stopright.h"
#include <QGraphicsScene>
#include <QMediaPlayer>

class PlayerPhysicsComponent : public PhysicsComponent
{
    QMediaPlayer * jump, * slip, * coin, * die, * ending;
public:
    //The constructor will initialize the parameters
    PlayerPhysicsComponent(std::vector< std::vector<Tile*> > &,qreal,qreal,qreal,qreal,QGraphicsScene*);
    void update(GameObject &);
};

#endif // PLAYERPHYSICSCOMPONENT_H
