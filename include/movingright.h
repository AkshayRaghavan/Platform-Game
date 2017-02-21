#ifndef MOVINGRIGHT_H
#define MOVINGRIGHT_H

#include "state.h"
#include "gameobject.h"
#include <Qt>
#include <set>

class MovingRight : public State
{
public:
    virtual ~MovingRight() {}
    virtual void update(GameObject &,std::set<Qt::key>);
};

#endif // MOVINGRIGHT_H
