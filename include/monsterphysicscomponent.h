#ifndef MONSTERPHYSICSCOMPONENT_H
#define MONSTERPHYSICSCOMPONENT_H

#include "physicscomponent.h"
#include "gameobject.h"
#include "tile.h"
#include <vector>

class MonsterPhysicsComponent : public PhysicsComponent
{
    Q_OBJECT
public:
    MonsterPhysicsComponent(std::vector< std::vector<Tile*> > &Tilesmap, int theight, int twidth, int sheight, int swidth);
    virtual ~MonsterPhysicsComponent() {}
    void update(GameObject &ob);
};

#endif // MONSTERPHYSICSCOMPONENT_H
