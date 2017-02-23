#ifndef ISJUMPING_H
#define ISJUMPING_H

#include "jumpingstate.h"
class InputComponent;

class IsJumping : public JumpingState
{
public:
    IsJumping(GameObject &);
    virtual ~IsJumping() {}
    virtual JumpingState* update(InputComponent *, GameObject &, std::set<Qt::Key>);
    virtual enumerator::JumpingState type();
};

#endif // ISJUMPING_H
