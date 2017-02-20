#ifndef STATE_H
#define STATE_H

#include "gameobject.h"

class State
{
    public:
        virtual State() {}
        virtual void update(const GameObject &) = 0;
};

#endif // STATE_H
