#include "include/jumpingleft.h"
#include "include/state.h"
#include "include/gameobject.h"
#include <Qt>
#include <set>
#include <algorithm>

virtual void JumpingLeft::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    int old_jump_count;
    if(key.find(gameObject.keys.right) != key.end() && key.find(gameObject.keys.jump) == key.end())
    {
        gameObject.state = State::MovingRight;
    }
    else if(key.find(gameObject.keys.left) != key.end() && key.find(gameObject.keys.jump) == key.end())
    {
        gameObject.state = State::MovingLeft;
    }
    else if(keys.find(gameObject.keys.jump) != key.end())
    {
        old_jump_count = gameObject.state.jumpCount;
        gameObject.state = State::Jumping;
        gameObject.state.jumpCount = old_jump_count;
    }
    else if(key.size() == 0)
    {
        gameObject.state = State::Stop;
    }
}
