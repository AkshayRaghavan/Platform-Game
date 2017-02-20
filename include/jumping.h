#ifndef JUMPING_H
#define JUMPING_H

#include "state.h"
#include "gameobject.h"

class Jumping : public State
{
public:
    virtual void update(const GameObject &);
};


#endif // JUMPING_H
