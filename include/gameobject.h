#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "inputcomponent.h"
#include "keys.h"
#include "state.h"
#include "jumpingstate.h"
#include "graphicscomponent.h"
#include "physicscomponent.h"
#include "scorecomponent.h"
#include <QObject>
#include <QGraphicsScene>
#include "enumerator.h"

class GameObject : public QObject
{
protected:
    bool acceptsInput;
    bool isDead;
    enumerator::ObjectType objecttype;
    int score;
public:
    const int maxJumpCount;
    void setIsDead(bool a);
    bool getIsDead();
    enumerator::ObjectType getObjectType();
    void setObjectType(enumerator::ObjectType a);
    GameObject(InputComponent *, GraphicsComponent *, PhysicsComponent * , ScoreComponent * , const int&);
    virtual ~GameObject() {}
    InputComponent *inputComponent;
    GraphicsComponent *graphicsComponent;
    PhysicsComponent *physicsComponent;
    ScoreComponent *scoreComponent;
    State *state;
    JumpingState *jumpingState;
    bool event(QEvent *) {}
    void setState(State*);
    void setJumpingState(JumpingState *);
    void setScore(int);
    int getScore();
    bool isAcceptingInput();
    void setAcceptingInput(bool value);
};

#endif // GAMEOBJECT_H
