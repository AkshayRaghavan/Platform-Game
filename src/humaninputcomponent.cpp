#include "include/humaninputcomponent.h"
#include "include/gameobject.h"
#include <QEvent>
#include <QKeyEvent>
#include <Qt>
#include <set>

HumanInputComponent::HumanInputComponent()
{
    keysPressed.clear();
}

virtual void HumanInputComponent::update(GameObject &gameObject)
{
    gameObject.state.update(GameObject,keysPressed);
}

void HumanInputComponent::event(QEvent *event, GameObject &gameObject)
{
    QKeyEvent *key_event = dynamic_cast<QKeyEvent *>(event);
    if(key_event && key_event->type() == QKeyEvent::KeyPress && gameObject.keys.find(key_event->key()) != gameObject.keys.end())
    {
        keysPressed.insert(key_event->key());
    }
    else if(key_event && key_event->type() == QKeyEvent::KeyRelease && gameObject.keys.find(key_event->key()) != gameObject.keys.end())
    {
        keysPressed.erase(key_event()->key());
    }
    update(gameObject);
}
