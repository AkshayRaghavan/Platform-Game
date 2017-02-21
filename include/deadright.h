#ifndef DEADRIGHT_H
#define DEADRIGHT_H

#include "state.h"
class GameObject;

class DeadRight : public State
{
public:
    virtual ~DeadRight() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
    virtual enumerator::State type();
};

#endif // DEADRIGHT_H
