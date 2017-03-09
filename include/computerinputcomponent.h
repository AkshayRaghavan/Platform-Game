#ifndef COMPUTERINPUTCOMPONENT_H
#define COMPUTERINPUTCOMPONENT_H

#include "inputcomponent.h"

/*! The input component to handle state changes for monsters in the game */

class ComputerInputComponent : public InputComponent
{
public:
    ComputerInputComponent() {}
    virtual ~ComputerInputComponent() {}
    virtual void update(GameObject &gameObject); //!< Updates the state values of gameObject */
    virtual bool acceptsInput(); //!< Returns whether the object the component belongs to accepts input
                                 //!< Here, false */
};

#endif // COMPUTERINPUTCOMPONENT_H
