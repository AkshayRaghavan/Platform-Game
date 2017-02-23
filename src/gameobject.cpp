#include "gameobject.h"
#include "movingleft.h"
#include "movingright.h"
#include "stopright.h"
#include "isjumping.h"
#include "isnotjumping.h"
#include <QCoreApplication>

enumerator::ObjectType GameObject::getObjectType()
{
    return objecttype;
}

void GameObject::setObjectType(enumerator::ObjectType a)
{
    objecttype = a;
}

GameObject::GameObject(InputComponent *input_component, GraphicsComponent *graphics_component, PhysicsComponent * physics_component , const int &max_jump_count) : maxJumpCount(max_jump_count)
{
    inputComponent = input_component;
    graphicsComponent = graphics_component;
    physicsComponent = physics_component;
    inputComponent->setParent(this);
    graphicsComponent->setParent(this);
    physicsComponent->setParent(this);
    state = new StopRight;
    jumpingState = new IsNotJumping;
    score = 0;
    acceptsInput = inputComponent->acceptsInput();
}

bool GameObject::event(QEvent *input_event)
{
    return QCoreApplication::sendEvent(inputComponent,input_event);
}

void GameObject::setState(State *input_state)
{
    if(input_state)
    {
        if(state)
        {
            delete this->state;
        }
        this->state = input_state;
    }
}

void GameObject::setJumpingState(JumpingState *input_jumping_state)
{
    if(input_jumping_state)
    {
        if(jumpingState)
        {
            delete this->jumpingState;
        }
        this->jumpingState = input_jumping_state;
    }
}

void GameObject::setScore(int x)
{
    score = x;
}

int GameObject::getScore()
{
    return score;
}

void GameObject::setIsDead(bool a)
{
    this->isDead = a;
}

bool GameObject::getIsDead()
{
    return this->isDead;
}

bool GameObject::isAcceptingInput()
{
    return this->acceptsInput;
}
