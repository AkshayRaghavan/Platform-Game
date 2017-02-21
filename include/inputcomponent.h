#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

class GameObject;
#include <QObject>

class InputComponent : public QObject
{
public:
    InputComponent();
    virtual ~InputComponent() {}
    virtual void update(GameObject &) {}
    virtual bool event(QEvent *);
};

#endif // INPUTCOMPONENT_H
