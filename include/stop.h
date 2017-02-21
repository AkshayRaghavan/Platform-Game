#ifndef STOP_H
#define STOP_H

#include "state.h"
class GameObject;
#include <Qt>
#include <set>

class Stop : public State
{
public:
    virtual ~Stop() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
};

#endif // STOP_H
