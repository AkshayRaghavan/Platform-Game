#include "gameobject.h"
#include <QCoreApplication>

enumerator::ObjectType GameObject::getObjectType()
{
    return objecttype;
}

void GameObject::setObjectType(enumerator::ObjectType a)
{
    objecttype = a;
}

GameObject::GameObject(InputComponent *input_component, Keys input_keys, const int &max_jump_count) : keys(input_keys), maxJumpCount(max_jump_count)
{
    inputComponent = input_component;
    inputComponent->setParent(this);
    graphicsComponent->setParent(this);
}

bool GameObject::event(QEvent *input_event)
{
    return QCoreApplication::sendEvent(inputComponent,input_event);
}
