#ifndef STATE_H
#define STATE_H

class GameObject;
class InputComponent;
#include "enumerator.h"
#include <Qt>
#include <set>

class State
{
public:
    virtual ~State() {}
    virtual State* update(InputComponent *,std::set<Qt::Key>) = 0;
    virtual enumerator::State type() = 0;
};

#endif // STATE_H
