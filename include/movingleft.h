#ifndef MOVINGLEFT_H
#define MOVINGLEFT_H

#include "state.h"
#include "gameobject.h"

class MovingLeft : public State
{
public:
    virtual void update(const GameObject &);
};


#endif // MOVINGLEFT_H
