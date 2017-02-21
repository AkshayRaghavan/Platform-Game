#include "include/state.h"
#include "include/gameobject.h"
#include <Qt>
#include <set>
#include <algorithm>

#include "include/movingleft.h"
#include "include/movingright.h"
#include "include/jumpingleft.h"
#include "include/jumpingright.h"
#include "include/jumping.h"
#include "include/stop.h"

State* JumpingRight::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    int old_jump_count;
    State *new_state = NULL;
    if(key.find(gameObject.keys.right) != key.end() && key.find(gameObject.keys.jump) == key.end())
    {
        new_state = new MovingRight;
    }
    else if(key.find(gameObject.keys.left) != key.end() && key.find(gameObject.keys.jump) == key.end())
    {
        new_state = new MovingLeft;
    }
    else if(key.find(gameObject.keys.jump) != key.end())
    {
        old_jump_count = gameObject.state->jumpCount;
        new_state = new Jumping;
        new_state->jumpCount = old_jump_count;
    }
    else if(key.size() == 0)
    {
        new_state = new Stop;
    }
    return new_state;
}
