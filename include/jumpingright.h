#ifndef JUMPINGRIGHT_H
#define JUMPINGRIGHT_H

#include "jumping.h"
class GameObject;
#include <Qt>
#include <set>

class JumpingRight : public Jumping
{
public:
    virtual ~JumpingRight() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
};

#endif // JUMPINGRIGHT_H
