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

    qreal setPosX, setPosY;
public:   

    QString name;
    int timeLeft;
    const int maxJumpCount;
    void setIsDead(bool a);
    bool getIsDead();
    enumerator::ObjectType getObjectType();
    void setObjectType(enumerator::ObjectType a);
    GameObject(InputComponent *, GraphicsComponent *, PhysicsComponent * , ScoreComponent * , const int& , int time_left = 0);
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
    void setName(QString);
    QString getName();
    int getTimeLeft();
    bool isAcceptingInput();
    void setAcceptingInput(bool value);
    void setPosXY(QPointF);
    QPointF getPosXY();
    void updatePos();
};

#endif // GAMEOBJECT_H
