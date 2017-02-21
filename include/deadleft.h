#ifndef DEADLEFT_H
#define DEADLEFT_H

#include "state.h"
class GameObject;
#include <Qt>
#include <set>

class DeadLeft : public State
{
public:
    virtual ~DeadLeft() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
};

#endif // DEADLEFT_H
