#include "humaninputcomponent.h"
#include "gameobject.h"
#include "state.h"
#include "jumpingstate.h"
#include <QKeyEvent>

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

bool HumanInputComponent::event(QEvent *event)
{
    QKeyEvent *key_event = dynamic_cast<QKeyEvent *>(event);
    GameObject *game_object = dynamic_cast<GameObject *>(this->parent());
    if(!key_event || !game_object)
    {
        return false;
    }
    if(key_event->type() == QKeyEvent::KeyPress && game_object->keys.find(static_cast<Qt::Key>(key_event->key())))
    {
        keysPressed.insert(static_cast<Qt::Key>(key_event->key()));
        update(*game_object);
        return true;
    }
    else if(key_event && key_event->type() == QKeyEvent::KeyRelease && game_object->keys.find(static_cast<Qt::Key>(key_event->key())))
    {
        keysPressed.erase(static_cast<Qt::Key>(key_event->key()));
        update(*game_object);
        return true;
    }
    return false;
}
