#include "include/movingleft.h"
#include "include/state.h"
#include <Qt>

virtual void MovingLeft::update(GameObject &gameObject, Qt::Key key)
{
    if(key == gameObject.keys.jump)
    {
        gameObject.state = State::Jumping;
    }
    else if(key == gameObject.keys.right)
    {
        gameObject.state = State::MovingRight;
    }
    else if(key == gameObject.keys.left)
    {
        gameObject.state = State::MovingLeft;
    }
}



