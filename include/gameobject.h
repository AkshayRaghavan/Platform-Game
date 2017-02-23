#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "inputcomponent.h"
#include "graphicscomponent.h"
#include "keys.h"
#include "state.h"
#include "jumpingstate.h"
#include "graphicscomponent.h"
#include "physicscomponent.h"
#include <QObject>
#include <QGraphicsScene>
#include "enumerator.h"

class GameObject : public QObject
{
protected:
    bool isDead;
    enumerator::ObjectType objecttype;
public:
    const int maxJumpCount;
    void setIsDead(bool a);
    bool getIsDead();
    enumerator::ObjectType getObjectType();
    void setObjectType(enumerator::ObjectType a);
    GameObject(InputComponent *, GraphicsComponent *, const int&);
    virtual ~GameObject() {}
    InputComponent *inputComponent;
    GraphicsComponent *graphicsComponent;
    PhysicsComponent *physicsComponent;
    State *state;
    JumpingState *jumpingState;
    bool event(QEvent *);
    void setState(State*);
    void setJumpingState(JumpingState *);
};

#endif // GAMEOBJECT_H
