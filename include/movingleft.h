#ifndef MOVINGLEFT_H
#define MOVINGLEFT_H

#include "state.h"
#include "gameobject.h"
#include <Qt>
#include <set>

class MovingLeft : public State
{
public:
    virtual ~MovingLeft() {}
    virtual void update(GameObject &,std::set<Qt::key>);
};


#endif // MOVINGLEFT_H
