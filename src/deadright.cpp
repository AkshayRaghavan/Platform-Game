#include "deadright.h"
#include "gameobject.h"

State* DeadRight::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    return NULL;
}

enumerator::State DeadRight::type()
{
    return enumerator::State::DEAD_RIGHT;
}
