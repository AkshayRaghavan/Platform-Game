#ifndef JUMPINGSTATE_H
#define JUMPINGSTATE_H

class GameObject;
class InputComponent;
#include "enumerator.h"
#include <Qt>
#include <set>

class JumpingState
{
public:
    int jumpCount;
    JumpingState();
    virtual ~JumpingState() {}
    virtual JumpingState* update(InputComponent *,GameObject &,std::set<Qt::Key>) = 0;
    virtual enumerator::JumpingState type() = 0;
    int getJumpCount();
    void setJumpCount(int);
    void jumpUpdate();
};

#endif // JUMPINGSTATE_H
