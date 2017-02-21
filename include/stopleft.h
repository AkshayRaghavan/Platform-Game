#ifndef STOPLEFT_H
#define STOPLEFT_H

#include "state.h"
class GameObject;
#include <Qt>
#include <set>

class StopLeft : public State
{
public:
    virtual ~StopLeft() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
};

#endif // STOPLEFT_H
