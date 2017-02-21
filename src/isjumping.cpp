#include "include/isjumping.h"
#include "include/jumpingstate.h"
#include "include/gameobject.h"
#include <Qt>
#include <set>
#include <algorithm>

IsJumping::IsJumping(GameObject &gameObject)
{
    jumpCount = gameObject.maxJumpCount;
}

JumpingState* IsJumping::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    return NULL;
}
