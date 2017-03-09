#ifndef ENUMERATOR_H
#define ENUMERATOR_H

/*!
 * \brief Class to store Enumerators used in the project
 */

namespace enumerator
{
    /*!
     * \brief The State enum
     * Stores the different states of a GameObject
     */
    enum class State { MOVING_RIGHT, MOVING_LEFT, STOP_RIGHT, STOP_LEFT, DEAD_RIGHT, DEAD_LEFT };

    /*!
     * \brief The JumpingState enum
     * Stores the different jumping states of a GameObject
     */
    enum class JumpingState { IS_JUMPING, IS_NOT_JUMPING };

    /*!
     * \brief The Identity enum
     * Stores whether the process is running a Server or a Client
     */
    enum class Identity { SERVER, CLIENT };

    /*!
     * \brief The ObjectType enum
     * Stores whether a player is a game player or a game monster
     */
    enum class ObjectType { PLAYER, ENEMY };
}

#endif // ENUMERATOR_H
