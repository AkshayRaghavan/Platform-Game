#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

class GameObject;

class InputComponent
{
public:
    InputComponent();
    virtual ~InputComponent() {}
    virtual void update(GameObject &) {}
};

#endif // INPUTCOMPONENT_H
