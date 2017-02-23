#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "inputcomponent.h"
#include "graphicscomponent.h"
#include "keys.h"
#include "state.h"
#include "jumpingstate.h"
#include <QObject>


class GameObject : public QObject
{
protected:
    bool isDead;
public:
    const int maxJumpCount;
    void setIsDead(bool a);
    bool getIsDead();
    GameObject(InputComponent *, GraphicsComponent *, Keys, const int&);
    virtual ~GameObject() {}
    InputComponent *inputComponent;
    GraphicsComponent *graphicsComponent;
    State *state;
    JumpingState *jumpingState;
    Keys keys;
    bool event(QEvent *);
    void setState(State*);
    void setJumpingState(JumpingState *);
};

#endif // GAMEOBJECT_H
