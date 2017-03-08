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
    if(!(gameObject.state))
    {
            qDebug() << "ERROR(computerinputcomponent.cpp) -> gameObject.state is NULL pointer";
            std::exit(EXIT_FAILURE);
    }
    if((gameObject.state->type() == enumerator::State::MOVING_LEFT || gameObject.state->type() == enumerator::State::STOP_LEFT) && (gameObject.physicsComponent->hasNoPlatformUnder(gameObject) || gameObject.physicsComponent->hasObstacleInFront(gameObject)))
    {
        gameObject.setState(new MovingRight);
    }
    else if((gameObject.state->type() == enumerator::State::MOVING_RIGHT || gameObject.state->type() == enumerator::State::STOP_RIGHT) && (gameObject.physicsComponent->hasNoPlatformUnder(gameObject) || gameObject.physicsComponent->hasObstacleInFront(gameObject)))
    {
        gameObject.setState(new MovingLeft);
    }
    else if(gameObject.state->type() == enumerator::State::STOP_LEFT)
    {
        gameObject.setState(new MovingLeft);
    }
    else if(gameObject.state->type() == enumerator::State::STOP_RIGHT)
    {
        gameObject.setState(new MovingRight);
    }
}

bool ComputerInputComponent::acceptsInput()
{
    return false;
}
