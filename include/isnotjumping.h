#ifndef ISNOTJUMPING_H
#define ISNOTJUMPING_H

#include "jumpingstate.h"
class InputComponent;

/*!
 * \brief JumpingState in which the GameObject is not jumping
 */

class IsNotJumping : public JumpingState
{
public:
    /*!
     * \brief Constructor
     * \param gameObject the GameObject the JumpingState belongs
     */
    IsNotJumping() {}

    /*!
     * \brief Destructor
     */
    virtual ~IsNotJumping() {}

    /*!
     * \brief Updates the JumpingState
     * \param input_component the InputComponent of the corresponding GameObject
     * \param game_object the corresponding GameObject
     * \param keys set of keys currently pressed
     * \return new JumpingState
     */
    virtual JumpingState* update(InputComponent *, GameObject &, std::set<Qt::Key>);

    /*!
     * \brief Get the type of the current JumpingState
     * \return value of enumerator::JumpingState with the type
     */
    virtual enumerator::JumpingState type();
};

#endif // ISNOTJUMPING_H
