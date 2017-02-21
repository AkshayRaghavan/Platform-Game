#include "include/gameobject.h"
#include "include/inputcomponent.h"
#include "include/keys.h"
#include "include/state.h"
#include <QObject>

GameObject::GameObject(InputComponent *input_component, Keys input_keys) : keys(input_keys)
{
    inputComponent = input_component;
}
