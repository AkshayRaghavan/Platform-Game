#include "gameobject.h"
#include "movingleft.h"
#include "movingright.h"
#include "stopright.h"
#include "isjumping.h"
#include "isnotjumping.h"
#include "deadright.h"
#include "monsterphysicscomponent.h"
#include "playerphysicscomponent.h"
#include <QCoreApplication>
#include <QDebug>

enumerator::ObjectType GameObject::getObjectType()
{
    return objecttype;
}

void GameObject::setObjectType(enumerator::ObjectType a)
{
    objecttype = a;
}

GameObject::GameObject(InputComponent *input_component, GraphicsComponent *graphics_component, PhysicsComponent * physics_component , ScoreComponent* score_component , const int &max_jump_count , int time_left)
    : maxJumpCount(max_jump_count)
{
    timeLeft = time_left;
    isDead = false;
    inputComponent = input_component;
    graphicsComponent = graphics_component;
    physicsComponent = physics_component;
    scoreComponent = score_component;
    inputComponent->setParent(this);
    graphicsComponent->setParent(this);
    physicsComponent->setParent(this);
    state = new StopRight;
    jumpingState = new IsNotJumping;
    score = 0;
    acceptsInput = inputComponent->acceptsInput();
}

/*bool GameObject::event(QEvent *input_event)
{*/
   // qDebug() << "received by game object";
/*    return *//*QCoreApplication::postEvent(inputComponent,input_event);
}*/

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

QString GameObject:: getName()
{
    return name;
}

void GameObject:: setName(QString name_local)
{
    name = name_local;
}

int GameObject::getTimeLeft()
{
    return timeLeft;
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

void GameObject::setAcceptingInput(bool value)
{
    this->acceptsInput = value;
}

void GameObject::setPosXY(QPointF point)
{
    setPosX = point.x();
    setPosY = point.y();
}

QPointF GameObject::getPosXY()
{
    return QPointF(setPosX, setPosY);
}

void GameObject::updatePos()
{
    if(typeid(*physicsComponent) == typeid(PlayerPhysicsComponent) || typeid(*physicsComponent) == typeid(MonsterPhysicsComponent))
    {
        graphicsComponent->setPos(setPosX, setPosY);
    }
}
