#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "inputcomponent.h"
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
    GameObject(InputComponent *, Keys, const int&);
    virtual ~GameObject() {}
    InputComponent *inputComponent;
    State *state;
    JumpingState *jumpingState;
    Keys keys;
    bool event(QEvent *);
    void setState(State*);
};

#endif // GAMEOBJECT_H
