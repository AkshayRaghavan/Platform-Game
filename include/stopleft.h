#ifndef STOPLEFT_H
#define STOPLEFT_H

#include "state.h"
class GameObject;

class StopLeft : public State
{
public:
    virtual ~StopLeft() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
    virtual enumerator::State type();
};

#endif // STOPLEFT_H
