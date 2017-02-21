#ifndef STATE_H
#define STATE_H

#include "gameobject.h"
#include <Qt>
#include <set>

class State
{
public:
    virtual State() {}
    virtual ~State() {}
    virtual void update(GameObject &,std::set<Qt::Key>) = 0;
};

#endif // STATE_H
