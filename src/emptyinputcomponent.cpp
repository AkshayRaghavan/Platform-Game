#include "emptyinputcomponent.h"


void EmptyInputComponent::update(GameObject &)
{
    return;
}

bool EmptyInputComponent::acceptsInput()
{
    return false;
}
