#ifndef JUMPINGSTATE_H
#define JUMPINGSTATE_H

class GameObject;
#include <Qt>
#include <set>

class JumpingState
{
protected:
    const int maxJumpCount;
public:
    int jumpCount;
    JumpingState(const int&);
    virtual ~JumpingState() {}
    virtual JumpingState* update(GameObject &,std::set<Qt::Key>) = 0;
};

#endif // JUMPINGSTATE_H
