#ifndef JUMPINGRIGHT_H
#define JUMPINGRIGHT_H

#include "jumping.h"
#include "gameobject.h"
#include <Qt>
#include <set>

class JumpingRight : public Jumping
{
public:
    virtual void update(GameObject &, std::set<Qt::key>);
};

#endif // JUMPINGRIGHT_H
