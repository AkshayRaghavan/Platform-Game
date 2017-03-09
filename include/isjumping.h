#ifndef ISJUMPING_H
#define ISJUMPING_H

#include "jumpingstate.h"
#include <QMediaPlayer>
class InputComponent;

/*!
 * \brief JumpingState in which the GameObject is jumping
 */

class IsJumping : public JumpingState
{
public:
    /*!
     * \brief Constructor
     * \param gameObject the GameObject the JumpingState belongs
     */
    IsJumping(GameObject &gameObject);

    /*!
     * \brief Destructor
     */
    virtual ~IsJumping() {}

    /*!
     * \brief Updates the JumpingState
     * \param input_component the InputComponent of the corresponding GameObject
     * \param game_object the corresponding GameObject
     * \param keys set of keys currently pressed
     * \return new JumpingState
     */
    virtual JumpingState* update(InputComponent *input_component, GameObject &game_object, std::set<Qt::Key> keys);

    /*!
     * \brief Get the type of the current JumpingState
     * \return value of enumerator::JumpingState with the type
     */
    virtual enumerator::JumpingState type();
};

#endif // ISJUMPING_H
