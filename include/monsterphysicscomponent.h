#ifndef MONSTERPHYSICSCOMPONENT_H
#define MONSTERPHYSICSCOMPONENT_H

#include "physicscomponent.h"
#include "gameobject.h"
#include "tile.h"

class MonsterPhysicsComponent : public PhysicsComponent
{private:
    int velocity;
public:
    MonsterPhysicsComponent();
    void update(GameObject &ob);
};

#endif // MONSTERPHYSICSCOMPONENT_H
