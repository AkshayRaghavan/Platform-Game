#ifndef ISNOTJUMPING_H
#define ISNOTJUMPING_H

#include "jumpingstate.h"

class IsNotJumping : public JumpingState
{
public:
    IsNotJumping(GameObject &);
    virtual ~IsNotJumping();
    virtual JumpingState* update(GameObject &, std::set<Qt::Key>);
    virtual enumerator::JumpingState type();
};

#endif // ISNOTJUMPING_H
