#ifndef MOVINGRIGHT_H
#define MOVINGRIGHT_H

#include "state.h"
class GameObject;
#include <Qt>
#include <set>

class MovingRight : public State
{
public:
    virtual ~MovingRight() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
};

#endif // MOVINGRIGHT_H
