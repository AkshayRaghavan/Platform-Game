#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class InputComponent;
#include "keys.h"
#include "state.h"
#include "jumpingstate.h"
#include <QObject>


class GameObject : public QObject
{
public:
    const int maxJumpCount;
    GameObject(InputComponent *, Keys, const int&);
    virtual ~GameObject() {}
    InputComponent *inputComponent;
    State *state;
    JumpingState *jumpingState;
    Keys keys;
};

#endif // GAMEOBJECT_H
