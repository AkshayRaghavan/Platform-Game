#ifndef DEADLEFT_H
#define DEADLEFT_H

#include "state.h"
class GameObject;

/*!
 * \brief The state in which the player is dead facing left
 * This also handles the responds to key press and key release inputs so as to change the state
 * of the GameObject
 */

class DeadLeft : public State
{
public:
    /*!
     * \brief Constructor
     */
    DeadLeft() {}

    /*!
     * \brief Destructor
     */
    ~DeadLeft() {}

    /*!
     * \brief Updates the state on the basis of the keys currently pressed
     * \param inputComponent the InputComponent of the GameObject whose state is being updated
     * \param key the set of keys currently pressed
     * \return the new state
     */
    State* update(InputComponent *inputComponent,std::set<Qt::Key> key);

    /*!
     * \brief Provides the type of the State, i.e., DeadLeft
     * \return enumerator::State::DEAD_LEFT
     */
    enumerator::State type();
};

#endif // DEADLEFT_H
