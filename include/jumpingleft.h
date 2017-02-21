#ifndef JUMPINGLEFT_H
#define JUMPINGLEFT_H

#include "jumping.h"
#include "gameobject.h"
#include <Qt>
#include <set>

class JumpingLeft : public Jumping
{
public:
    virtual ~JumpingLeft() {}
    virtual void update(GameObject &, std::set<Qt::key>);
};

#endif // JUMPINGLEFT_H
