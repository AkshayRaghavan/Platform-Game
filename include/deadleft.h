#ifndef DEADLEFT_H
#define DEADLEFT_H

#include "state.h"
class GameObject;

class DeadLeft : public State
{
public:
    DeadLeft() {}
    ~DeadLeft() {}
    State* update(InputComponent *,std::set<Qt::Key>);
    enumerator::State type();
};

#endif // DEADLEFT_H
