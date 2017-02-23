#include "isjumping.h"
#include "gameobject.h"
#include <algorithm>

IsJumping::IsJumping(GameObject &gameObject)
{
    jumpCount = gameObject.maxJumpCount;
}

JumpingState* IsJumping::update(InputComponent *inputComponent, GameObject &gameObject, std::set<Qt::Key> key)
{
    return NULL;
}

enumerator::JumpingState IsJumping::type()
{
    return enumerator::JumpingState::IS_JUMPING;
}
