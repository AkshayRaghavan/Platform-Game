#ifndef HUMANINPUTCOMPONENT_H
#define HUMANINPUTCOMPONENT_H

#include "inputcomponent.h"
#include <QEvent>
#include <Qt>
#include <set>

class HumanInputComponent : public InputComponent
{
    std::set<Qt::Key> keysPressed;
public:
    HumanInputComponent(Keys *keys);
    virtual ~HumanInputComponent() {}
    virtual void update(GameObject &);
    bool event(QEvent *);

};

#endif // HUMANINPUTCOMPONENT_H
