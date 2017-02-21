#ifndef STOP_H
#define STOP_H

#include "state.h"
#include "gameobject.h"
#include <Qt>
#include <set>

class Stop : public State
{
public:
    virtual ~Stop() {}
    virtual void update(GameObject &,std::set<Qt::key>);
};

#endif // STOP_H
