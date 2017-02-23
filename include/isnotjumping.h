#ifndef ISNOTJUMPING_H
#define ISNOTJUMPING_H

#include "jumpingstate.h"
class InputComponent;

class IsNotJumping : public JumpingState
{
public:
    IsNotJumping() {}
    virtual ~IsNotJumping() {}
    virtual JumpingState* update(InputComponent *, GameObject &, std::set<Qt::Key>);
    virtual enumerator::JumpingState type();
};

#endif // ISNOTJUMPING_H
