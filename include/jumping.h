#ifndef JUMPING_H
#define JUMPING_H

#include "state.h"
class GameObject;
#include <Qt>
#include <set>

class Jumping : public State
{
public:
    int jumpCount;
    Jumping();
    virtual ~Jumping() {}
    virtual void update(GameObject &,std::set<Qt::Key>);
};


#endif // JUMPING_H
