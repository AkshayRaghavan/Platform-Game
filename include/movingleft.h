#ifndef MOVINGLEFT_H
#define MOVINGLEFT_H

#include "state.h"
class GameObject;
#include <Qt>
#include <set>

class MovingLeft : public State
{
public:
    virtual ~MovingLeft() {}
    virtual void update(GameObject &,std::set<Qt::Key>);
};


#endif // MOVINGLEFT_H
