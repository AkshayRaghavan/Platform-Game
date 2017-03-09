#include "deadleft.h"
#include "gameobject.h"

State* DeadLeft::update(InputComponent *inputComponent, std::set<Qt::Key> key)
{
    return NULL;
}

enumerator::State DeadLeft::type()
{
    return enumerator::State::DEAD_LEFT;
}
