#ifndef JUMPING_H
#define JUMPING_H

#include "state.h"
#include "gameobject.h"
#include <Qt>
#include <set>

class Jumping : public State
{
public:
    int jumpCount;
    Jumping();
    virtual ~Jumping() {}
    virtual void update(GameObject &,std::set<Qt::key>);
};


#endif // JUMPING_H
