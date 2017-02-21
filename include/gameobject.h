#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "inputcomponent.h"
#include "keys.h"
#include "state.h"
#include <QObject>


class GameObject : public QObject
{
public:
    GameObject(InputComponent *, Keys);
    virtual ~GameObject() {}
    InputComponent *inputComponent;
    State state;
    Keys keys;
};

#endif // GAMEOBJECT_H
