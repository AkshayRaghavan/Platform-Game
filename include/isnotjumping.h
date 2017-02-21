#ifndef ISNOTJUMPING_H
#define ISNOTJUMPING_H

#include "jumpingstate.h"
class GameObject;

class IsNotJumping : public JumpingState
{
public:
    IsNotJumping(const int&);
    virtual ~IsNotJumping();
    virtual JumpingState* update(GameObject &, std::set<Qt::Key>);
};

#endif // ISNOTJUMPING_H
