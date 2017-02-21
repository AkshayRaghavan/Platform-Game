#include "isnotjumping.h"
#include "isjumping.h"
#include "jumpingstate.h"
#include "gameobject.h"
#include <Qt>
#include <set>
#include <algorithm>

//IsNotJumping::IsNotJumping(const int& max_jump_count) : JumpingState(max_jump_count) {}

JumpingState* IsNotJumping::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    JumpingState *new_state = NULL;
    if(key.find(gameObject.keys.jump) != key.end())
    {
        new_state = new IsJumping(gameObject);
    }
    return new_state;
}
