#ifndef DEADRIGHT_H
#define DEADRIGHT_H

#include "state.h"
class GameObject;

class DeadRight : public State
{
public:
    DeadRight() {}
    ~DeadRight() {}
    State* update(InputComponent *,std::set<Qt::Key>);
    enumerator::State type();
};

#endif // DEADRIGHT_H
