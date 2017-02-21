#ifndef JUMPINGLEFT_H
#define JUMPINGLEFT_H

#include "jumping.h"
class GameObject;
#include <Qt>
#include <set>

class JumpingLeft : public Jumping
{
public:
    virtual ~JumpingLeft() {}
    virtual void update(GameObject &, std::set<Qt::Key>);
};

#endif // JUMPINGLEFT_H
