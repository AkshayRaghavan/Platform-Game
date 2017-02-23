#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

class GameObject;
#include <QObject>
#include "keys.h"

class InputComponent : public QObject
{
public:
    Keys *keys;
    InputComponent();
    virtual ~InputComponent() {}
    virtual void update(GameObject &) {}
    virtual bool event(QEvent *);
    virtual bool acceptsInput() = 0;
};

#endif // INPUTCOMPONENT_H
