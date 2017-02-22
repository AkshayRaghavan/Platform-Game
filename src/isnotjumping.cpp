#include "isnotjumping.h"
#include "isjumping.h"
#include "gameobject.h"
#include <algorithm>

JumpingState* IsNotJumping::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    JumpingState *new_state = NULL;
    if(key.find(gameObject.keys.jump) != key.end())
    {
        new_state = new IsJumping(gameObject);
    }
    return new_state;
}

enumerator::JumpingState IsNotJumping::type()
{
    return enumerator::JumpingState::IS_NOT_JUMPING;
}
