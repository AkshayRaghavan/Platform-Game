#ifndef MOVINGRIGHT_H
#define MOVINGRIGHT_H

#include "state.h"
class GameObject;

class MovingRight : public State
{
public:
    virtual ~MovingRight() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
    virtual enumerator::State type();
};

#endif // MOVINGRIGHT_H
