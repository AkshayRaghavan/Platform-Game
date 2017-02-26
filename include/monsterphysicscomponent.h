#ifndef MONSTERPHYSICSCOMPONENT_H
#define MONSTERPHYSICSCOMPONENT_H

#include "physicscomponent.h"
#include "gameobject.h"
#include "tile.h"
#include <vector>

class MonsterPhysicsComponent : public PhysicsComponent
{
public:
    MonsterPhysicsComponent(std::vector< std::vector<Tile*> > &Tilesmap, qreal theight, qreal twidth, qreal sheight, qreal swidth);
    virtual ~MonsterPhysicsComponent() {}
    void update(GameObject &ob);
};

#endif // MONSTERPHYSICSCOMPONENT_H
