#ifndef HUMANINPUTCOMPONENT_H
#define HUMANINPUTCOMPONENT_H

#include "inputcomponent.h"
class GameObject;
#include <QEvent>
#include <Qt>
#include <set>

class HumanInputComponent : public InputComponent
{
    std::set<Qt::Key> keysPressed;
public:
    HumanInputComponent();
    virtual ~HumanInputComponent() {}
    virtual void update(GameObject &);
    void event(QEvent *, GameObject &);
};

#endif // HUMANINPUTCOMPONENT_H
