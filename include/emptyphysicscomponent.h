#ifndef EMPTYPHYSICSCOMPONENT_H
#define EMPTYPHYSICSCOMPONENT_H

#include "physicscomponent.h"

class EmptyPhysicsComponent : public PhysicsComponent
{
public:
    EmptyPhysicsComponent() {}
    virtual ~EmptyPhysicsComponent() {}
    void update(GameObject &);
};

#endif // EMPTYPHYSICSCOMPONENT_H
