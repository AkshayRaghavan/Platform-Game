#include "include/humaninputcomponent.h"
#include "include/gameobject.h"
#include "include/state.h"
#include "include/jumpingstate.h"
#include <QEvent>
#include <QKeyEvent>
#include <Qt>
#include <set>



HumanInputComponent::HumanInputComponent()
{
    keysPressed.clear();
}

void HumanInputComponent::update(GameObject &gameObject)
{
    State *new_state = gameObject.state->update(gameObject,keysPressed);
    JumpingState *new_jumping_state = gameObject.jumpingState->update(gameObject,keysPressed);
    if(new_state != NULL)
    {
        delete gameObject.state;
        gameObject.state = new_state;
    }
    if(new_jumping_state != NULL)
    {
        delete gameObject.jumpingState;
        gameObject.jumpingState = new_jumping_state;
    }

}

void HumanInputComponent::event(QEvent *event, GameObject &gameObject)
{
    QKeyEvent *key_event = dynamic_cast<QKeyEvent *>(event);
    if(key_event && key_event->type() == QKeyEvent::KeyPress && gameObject.keys.find(static_cast<Qt::Key>(key_event->key())))
    {
        keysPressed.insert(static_cast<Qt::Key>(key_event->key()));
    }
    else if(key_event && key_event->type() == QKeyEvent::KeyRelease && gameObject.keys.find(static_cast<Qt::Key>(key_event->key())))
    {
        keysPressed.erase(static_cast<Qt::Key>(key_event->key()));
    }
    update(gameObject);
}
