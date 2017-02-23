#include "movingright.h"
#include "movingleft.h"
#include "stopright.h"
#include "gameobject.h"
#include <Qt>
#include <set>
#include <algorithm>

State* MovingRight::update(InputComponent *inputComponent, std::set<Qt::Key> key)
{
    State *new_state = NULL;
    if(key.find(inputComponent->keys->right) != key.end())
    {
        new_state = new MovingRight;
    }
    else if(key.find(inputComponent->keys->left) != key.end())
    {
        new_state = new MovingLeft;
    }
    else if(key.size() == 0)
    {
        new_state = new StopRight;
    }
    return new_state;
}

enumerator::State MovingRight::type()
{
    return enumerator::State::MOVING_RIGHT;
}
