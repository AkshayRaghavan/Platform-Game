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
#include <typeinfo>

/*!
 * \brief A Game Object
 * This represents all the Game Objects in the game, including players, monsters and fire
 * and the way to create them, display them, move them, and update state *
 */


class GameObject : public QObject
{
protected:
    /*!
     * \brief Specifies whether the GameObject accepts keyboard input
     */
    bool acceptsInput;

    /*!
     * \brief Specifies whether the GameObject is alive, applicable to players
     */
    bool isDead;

    /*!
     * \brief Specifies whether the GameObject is a player or a monster, value undefined otherwise
     */
    enumerator::ObjectType objecttype;

    /*!
     * \brief Specifies the score of the GameObject, applicable to players
     */
    int score;

    /*!
     * \brief Specifies where the GameObject needs to be placed in the
     */
    qreal setPosX;
    qreal setPosY;
public:   

    QString name;
    int timeLeft;
    const int maxJumpCount;

    void setIsDead(bool a);
    bool getIsDead();
    enumerator::ObjectType getObjectType();
    void setObjectType(enumerator::ObjectType a);
    GameObject(InputComponent *, GraphicsComponent *, PhysicsComponent * , ScoreComponent * , const int& , int time_left = 0);
    ~GameObject();
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
