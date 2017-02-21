#ifndef MOVINGLEFT_H
#define MOVINGLEFT_H

#include "state.h"
class GameObject;

class MovingLeft : public State
{
public:
    virtual ~MovingLeft() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
    virtual enumerator::State type();
};


#endif // MOVINGLEFT_H
