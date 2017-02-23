#include "deadleft.h"
#include "gameobject.h"

State* DeadLeft::update(InputComponent *gameObject, std::set<Qt::Key> key)
{
    return NULL;
}

enumerator::State DeadLeft::type()
{
    return enumerator::State::DEAD_LEFT;
}
