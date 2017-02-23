#include "stopright.h"
#include "movingleft.h"
#include "movingright.h"
#include "gameobject.h"
#include <Qt>
#include <set>
#include <algorithm>

State* StopRight::update(GameObject &gameObject, std::set<Qt::Key> key)
{
    State *new_state = NULL;
    if(key.find(gameObject.keys.right) != key.end())
    {
        new_state = new MovingRight;
    }
    else if(key.find(gameObject.keys.left) != key.end())
    {
        new_state = new MovingLeft;
    }
    else if(key.size() == 0)
    {
        new_state = new StopRight;
    }
    return new_state;
}

enumerator::State StopRight::type()
{
    return enumerator::State::STOP_RIGHT;
}


