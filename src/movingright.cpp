#include "include/jumpingleft.h"
#include "include/state.h"
#include "gameobject.h"
#include <Qt>
#include <set>
#include <algorithm>

virtual void MovingRight::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    if(key.find(gameObject.keys.right) != key.end())
    {
        if(key.find(gameObject.keys.jump) != key.end())
        {
             gameObject.state = State::JumpingRight;
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
             gameObject.state = State::JumpingLeft;
        }
        else
        {
            gameObject.state = State::MovingLeft;
        }
    }
    else if(key.find(gameObject.keys.jump) != key.end())
    {
        gameObject.state = State::Jumping;
    }
    else if(keys.size() == 0)
    {
        gameObject.state = State::Stop;
    }
}
