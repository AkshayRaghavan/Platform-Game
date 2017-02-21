#include "include/jumping.h"
#include "include/state.h"
#include "include/gameobject.h"
#include <Qt>
#include <set>
#include <algorithm>

Jumping::Jumping()
{
    jumpCount = 0;
}

virtual void Jumping::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    int old_jump_count;
    if(key.find(gameObject.keys.right) != key.end())
    {
        if(key.find(gameObject.keys.jump) != key.end())
        {
             old_jump_count = gameObject.state.jumpCount;
             gameObject.state = State::JumpingRight;
             gameObject.state.jumpCount = old_jump_count;
        }
        else
        {
            gameObject.state = State::MovingRight;
        }

    }
    else if(key.find(gameObject.keys.left) != key.end())
    {
        if(key.find(gameObject.keys.jump) != key.end())
        {
            old_jump_count = gameObject.state.jumpCount;
            gameObject.state = State::JumpingLeft;
            gameObject.state.jumpCount = old_jump_count;
        }
        else
        {
            gameObject.state = State::MovingLeft;
        }
    }
    else if(keys.size() == 0)
    {
        gameObject.state = State::Stop;
    }
}

