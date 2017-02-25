#ifndef EMPTYINPUTCOMPONENT_H
#define EMPTYINPUTCOMPONENT_H

#include "inputcomponent.h"

class EmptyInputComponent : public InputComponent
{
public:
    EmptyInputComponent() {}
    virtual ~EmptyInputComponent() {}
    virtual void update(GameObject &);
    virtual bool acceptsInput();
};

#endif // EMPTYINPUTCOMPONENT_H
