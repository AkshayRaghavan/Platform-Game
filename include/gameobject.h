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
     * \brief Specifies x coordinate where the GameObject needs to be placed in the next frame
     */
    qreal setPosX;

    /*!
     * \brief Specifies y coordinate where the GameObject needs to be placed in the next frame
     */
    qreal setPosY;
public:   
    /*!
     * \brief Stores the username, applies to players
     */
    QString name;

    /*!
     * \brief Stores the time left when the player completed the game, applies to players
     */
    int timeLeft;

    /*!
     * \brief Specifies the number of frames the GameObject moves up on jumping
     */
    const int maxJumpCount;

    /*!
     * \brief Sets the value of isDead
     * \param input the new value of isDead
     */
    void setIsDead(bool input);

    /*!
     * \brief Get the value of isDead
     * \return value of isDead
     */
    bool getIsDead();

    /*!
     * \brief Get the value of objecttype
     * \return value of objecttype
     */
    enumerator::ObjectType getObjectType();

    /*!
     * \brief Sets the value of objecttype
     * \param input the new value of objecttype
     */
    void setObjectType(enumerator::ObjectType input);

    /*!
     * \brief Constructor
     * \param input_component value of inputComponent
     * \param graphics_component value of graphicsComponent
     * \param physics_component value of physicsComponent
     * \param score_component value of scoreComponent
     * \param max_jump_count value of maxJumpCount
     * \param time_left time available for the GameObject to play in the game when started
     */
    GameObject(InputComponent *input_component, GraphicsComponent *graphics_component, PhysicsComponent * physics_component , ScoreComponent* score_component , const int &max_jump_count , int time_left = 0);

    /*!
     * \brief Destructor
     */
    virtual ~GameObject() {}

    /*!
     * \brief Component that handles input
     * Handles keyboard input and state changes of the GameObject, and sets states appropriately
     */
    InputComponent *inputComponent;

    /*!
     * \brief Component that handles graphics
     * Handles the drawing of the GameObject on the sceen, stores how it is drawn, and updates based on state
     */
    GraphicsComponent *graphicsComponent;

    /*!
     * \brief Component that handles physics
     * Handles the movement of GameObject based on the current state, and updates the current position on the scene
     */
    PhysicsComponent *physicsComponent;

    /*!
     * \brief Component that handles score
     * Handles the score of the GameObject, the display of the score, and updates the score. Applies to players.
     */
    ScoreComponent *scoreComponent;

    /*!
     * \brief State of the GameObject
     * Stores the state of the GameObject, in particular the state of its motion in the x direction
     * Includes Moving Left, Moving Right, Stationary facing left, Stationary facing right
     * Dead facing left, Dead facing right
     * Also handles changes to the state based on the current key combination
     */
    State *state;

    /*!
     * \brief Jumping State of the GameObject
     * Stores the Jumping State of the GameObject, and consists of IsJumping and IsNotJumping
     * Also handles changes to the JumpingState based on the current key combination
     */
    JumpingState *jumpingState;

    /*!
     * \brief Sets the value of sate
     * \param input_state the new value of state
     */
    void setState(State* input_state);

    /*!
     * \brief Sets the value of jumpingState
     * \param input_jumping_state the new value of jumpingState
     */
    void setJumpingState(JumpingState *input_jumping_state);

    /*!
     * \brief Sets the score of the GameObject
     * \param input_score the new value of score
     */
    void setScore(int input_score);

    /*!
     * \brief Get the value of score
     * \return the value of score
     */
    int getScore();

    /*!
     * \brief Sets the user name of the GameObject, applies to players
     * \param name_local the new value of the user name
     */
    void setName(QString name_local);

    /*!
     * \brief Get the user name of the GameObject, applies to players
     * \return the value of the user name
     */
    QString getName();

    /*!
     * \brief Get the time left for the GameObject in the game, applies to players
     * \return the value of the time left
     */
    int getTimeLeft();

    /*!
     * \brief Get whether the GameObject accepts input from the keyboard
     * \return true, if the GameObject accepts input, false otherwise
     */
    bool isAcceptingInput();

    /*!
     * \brief Set whether the GameObject accepts input from the keyboard
     * \param value the new value, true if it accepts, false otherwise
     */
    void setAcceptingInput(bool value);

    /*!
     * \brief Set the position of the GameObject in the next frame
     * \param point the point to which the GameObject must go the next frame
     */
    void setPosXY(QPointF point);

    /*!
     * \brief Get the position where the GameObject will go in the next frame
     * \return the point
     */
    QPointF getPosXY();

    /*!
     * \brief Update the position of the player
     */
    void updatePos();
};

#endif // GAMEOBJECT_H
