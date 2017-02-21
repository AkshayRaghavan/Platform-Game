#include "include/state.h"
#include "include/gameobject.h"
#include <Qt>
#include <set>
#include <algorithm>

#include "include/jumping.h"

Jumping::Jumping()
{
    jumpCount = 0;
}

virtual State Jumping::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    int old_jump_count;
    State *new_state;
    if(key.find(gameObject.keys.right) != key.end())
    {
        if(key.find(gameObject.keys.jump) != key.end())
        {
             old_jump_count = gameObject.state.jumpCount;
             new_state = new JumpingRight;
             new_state->jumpCount = old_jump_count;
        }
        else
        {
            gameObject.state = State::movingRight;
        }

    }
    else if(key.find(gameObject.keys.left) != key.end())
    {
        if(key.find(gameObject.keys.jump) != key.end())
        {
            old_jump_count = gameObject.state.jumpCount;
            gameObject.state = State::jumpingLeft;
            gameObject.state.jumpCount = old_jump_count;
        }
        else
        {
            gameObject.state = State::movingLeft;
        }
    }
    else if(key.size() == 0)
    {
        gameObject.state = State::stop;
    }
}

