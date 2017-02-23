#include "humaninputcomponent.h"
#include "gameobject.h"
#include "state.h"
#include "jumpingstate.h"
#include <QKeyEvent>
#include "movingleft.h"
#include "movingright.h"
#include "isjumping.h"
#include "isnotjumping.h"

HumanInputComponent::HumanInputComponent(Keys *input_keys)
{
    keysPressed.clear();
    keys = input_keys;
}

void HumanInputComponent::update(GameObject &gameObject)
{
    State *new_state = gameObject.state->update(gameObject.inputComponent,keysPressed);
    JumpingState *new_jumping_state = gameObject.jumpingState->update(gameObject.inputComponent,gameObject,keysPressed);
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
    if(key_event->type() == QKeyEvent::KeyPress && keys->find(static_cast<Qt::Key>(key_event->key())))
    {
        keysPressed.insert(static_cast<Qt::Key>(key_event->key()));
        update(*game_object);
        return true;
    }
    else if(key_event && key_event->type() == QKeyEvent::KeyRelease && keys->find(static_cast<Qt::Key>(key_event->key())))
    {
        keysPressed.erase(static_cast<Qt::Key>(key_event->key()));
        update(*game_object);
        return true;
    }
    return false;
}

bool HumanInputComponent::acceptsInput()
{
    return true;
}
