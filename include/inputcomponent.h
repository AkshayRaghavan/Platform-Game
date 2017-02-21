#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "gameobject.h"

class InputComponent
{
public:
    virtual ~InputComponent() {}
    virtual void update(GameObject &) = 0;
};

#endif // INPUTCOMPONENT_H
