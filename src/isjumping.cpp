#include "include/isjumping.h"
#include "include/jumpingstate.h"
#include "include/gameobject.h"
#include <Qt>
#include <set>
#include <algorithm>

IsJumping::IsJumping(const int& max_jump_count) : JumpingState(max_jump_count) {}

JumpingState* IsJumping::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    return NULL;
}
