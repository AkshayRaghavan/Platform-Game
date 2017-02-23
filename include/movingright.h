#ifndef MOVINGRIGHT_H
#define MOVINGRIGHT_H

#include "state.h"
class InputComponent;
class GameObject;

class MovingRight : public State
{
public:
    virtual ~MovingRight() {}
    virtual State* update(InputComponent *,std::set<Qt::Key>);
    virtual enumerator::State type();
};

#endif // MOVINGRIGHT_H
