#ifndef COMPUTERINPUTCOMPONENT_H
#define COMPUTERINPUTCOMPONENT_H

#include "inputcomponent.h"

class ComputerInputComponent : public InputComponent
{
protected:
    int numberOfFramesPerDirection;
    int currentNumberOfFrames;
public:
    ComputerInputComponent(int);
    virtual ~ComputerInputComponent() {}
    virtual void update(GameObject &);
};

#endif // COMPUTERINPUTCOMPONENT_H
