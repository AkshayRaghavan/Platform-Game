#include "gameobject.h"
#include "movingleft.h"
#include "movingright.h"
#include "isjumping.h"
#include "isnotjumping.h"
#include <QCoreApplication>

GameObject::GameObject(InputComponent *input_component, GraphicsComponent *graphics_component, const int &max_jump_count) : maxJumpCount(max_jump_count)
{
    inputComponent = input_component;
    graphicsComponent = graphics_component;
    inputComponent->setParent(this);
    setState(new MovingRight);
    setJumpingState(new IsNotJumping);
}

bool GameObject::event(QEvent *input_event)
{
    return QCoreApplication::sendEvent(inputComponent,input_event);
}

void GameObject::setState(State *input_state)
{
    delete this->state;
    this->state = input_state;
}

void GameObject::setJumpingState(JumpingState *input_jumping_state)
{
    delete this->jumpingState;
    this->jumpingState = input_jumping_state;
}

void GameObject::setIsDead(bool a)
{
    this->isDead = a;
}

bool GameObject::getIsDead()
{
    return this->isDead;
}
