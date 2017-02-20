#ifndef MOVINGRIGHT_H
#define MOVINGRIGHT_H

#include "state.h"
#include "gameobject.h"

class MovingRight : public State
{
public:
    virtual void update(const GameObject &);
};

#endif // MOVINGRIGHT_H
