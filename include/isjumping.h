#ifndef ISJUMPING_H
#define ISJUMPING_H

#include "jumpingstate.h"
class GameObject;

class IsJumping : public JumpingState
{
public:
    IsJumping(GameObject &);
    virtual ~IsJumping() {}
    virtual JumpingState* update(GameObject &, std::set<Qt::Key>);
};

#endif // ISJUMPING_H
