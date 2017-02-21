#include "include/state.h"
#include "include/gameobject.h"
#include <Qt>
#include <set>
#include <algorithm>

#include "include/jumpingright.h"

virtual void JumpingRight::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    int old_jump_count;
    if(key.find(gameObject.keys.right) != key.end() && key.find(gameObject.keys.jump) == key.end())
    {
        gameObject.state = State::movingRight;
    }
    else if(key.find(gameObject.keys.left) != key.end() && key.find(gameObject.keys.jump) == key.end())
    {
        gameObject.state = State::movingLeft;
    }
    else if(keys.find(gameObject.keys.jump) != key.end())
    {
        old_jump_count = gameObject.state.jumpCount;
        gameObject.state = State::jumping;
        gameObject.state.jumpCount = old_jump_count;
    }
    else if(key.size() == 0)
    {
        gameObject.state = State::stop;
    }
}
