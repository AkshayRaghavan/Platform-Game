#ifndef DEADLEFT_H
#define DEADLEFT_H

#include "state.h"
class GameObject;

class DeadLeft : public State
{
public:
    virtual ~DeadLeft() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
    virtual enumerator::State type();
};

#endif // DEADLEFT_H
