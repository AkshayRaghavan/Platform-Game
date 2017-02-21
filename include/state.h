#ifndef STATE_H
#define STATE_H

class GameObject;
#include <Qt>
#include <set>

class State
{
public:
    virtual ~State() {}
    virtual State* update(GameObject &,std::set<Qt::Key>) = 0;
};

#endif // STATE_H
