#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "gameobject.h"

class InputComponent
{
public:
    virtual void update(GameObject &);
};

#endif // INPUTCOMPONENT_H
