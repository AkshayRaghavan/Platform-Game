#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "inputcomponent.h"
#include "keys.h"
#include "state.h"
#include "jumpingstate.h"
#include "graphicscomponent.h"
#include "physicscomponent.h"
#include <QObject>
#include <QGraphicsScene>


class GameObject : public QObject
{
private:
        bool isDead;
public:
    const int maxJumpCount;
    inline void setIsDead(bool a){
        this->isDead = a;
    }
    inline bool getIsDead(){
        return this->isDead;
    }
    GameObject(InputComponent *, Keys, const int&);
    virtual ~GameObject() {}
    InputComponent *inputComponent;
    GraphicsComponent *graphicscomponent;
    PhysicsComponent *physicscomponent;
    State *state;
    JumpingState *jumpingState;
    QGraphicsScene * scene;
    Keys keys;
    bool event(QEvent *);
};

#endif // GAMEOBJECT_H
