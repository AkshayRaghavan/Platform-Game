#include "include/state.h"
#include "include/gameobject.h"
#include <Qt>
#include <set>
#include <algorithm>

#include "include/movingright.h"

virtual void MovingRight::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    if(key.find(gameObject.keys.right) != key.end())
    {
        if(key.find(gameObject.keys.jump) != key.end())
        {
             gameObject.state = State::jumpingRight;
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
             gameObject.state = State::jumpingLeft;
        }
        else
        {
            gameObject.state = State::movingLeft;
        }
    }
    else if(key.find(gameObject.keys.jump) != key.end())
    {
        gameObject.state = State::jumping;
    }
    else if(key.size() == 0)
    {
        gameObject.state = State::stop;
    }
}
