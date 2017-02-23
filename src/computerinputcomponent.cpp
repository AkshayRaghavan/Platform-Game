#include "computerinputcomponent.h"
#include "gameobject.h"
#include "movingleft.h"
#include "movingright.h"
#include "isjumping.h"
#include "isnotjumping.h"

ComputerInputComponent::ComputerInputComponent(int walk_frames_count)
{
    numberOfFramesPerDirection = walk_frames_count;
    currentNumberOfFrames = walk_frames_count;
}

void ComputerInputComponent::update(GameObject &gameObject)
{
    if(currentNumberOfFrames == 0 && gameObject.state->type() == enumerator::State::MOVING_LEFT)
    {
        gameObject.setState(new MovingRight);
        currentNumberOfFrames = numberOfFramesPerDirection;

    }
    else if(currentNumberOfFrames == 0 && gameObject.state->type() == enumerator::State::MOVING_RIGHT)
    {
        gameObject.setState(new MovingLeft);
        currentNumberOfFrames = numberOfFramesPerDirection;
    }
    else
    {
        currentNumberOfFrames --;
    }
}

bool ComputerInputComponent::acceptsInput()
{
    return false;
}
