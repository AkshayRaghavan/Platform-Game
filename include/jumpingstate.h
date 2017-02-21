#ifndef JUMPINGSTATE_H
#define JUMPINGSTATE_H

class GameObject;
#include "enumerator.h"
#include <Qt>
#include <set>

class JumpingState
{
public:
    int jumpCount;
    JumpingState();
    virtual ~JumpingState() {}
    virtual JumpingState* update(GameObject &,std::set<Qt::Key>) = 0;
    virtual enumerator::JumpingState type() = 0;
    int getJumpCount();
    void setJumpCount(int);
    void jumpUpdate();
};

#endif // JUMPINGSTATE_H
