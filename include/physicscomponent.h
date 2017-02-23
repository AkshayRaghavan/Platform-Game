#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

class GameObject;
#include <QObject>

class PhysicsComponent : public QObject
{
public:
    PhysicsComponent() {}
    virtual ~PhysicsComponent() {}
    virtual void update (GameObject &);
};

#endif // PHYSICSCOMPONENT_H
