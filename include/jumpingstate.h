#ifndef JUMPINGSTATE_H
#define JUMPINGSTATE_H

class GameObject;
class InputComponent;
#include "enumerator.h"
#include <Qt>
#include <set>

/*!
 * \brief This class is used to store whether the player is jumping or not
 */

class JumpingState
{
public:
    /*!
     * \brief To store how long the player is in air
     */
    int jumpCount;
    /*!
     * \brief Constructor for Jumping State
     */
    JumpingState();
    /*!
     * \brief Destructor
     */
    virtual ~JumpingState() {}
    /*!
     * \brief To update the Jumping State of the Game Object
     * \return
     */
    virtual JumpingState* update(InputComponent *,GameObject &,std::set<Qt::Key>) = 0;
    /*!
     * \brief To return the Type of Jumping state
     * \return
     */
    virtual enumerator::JumpingState type() = 0;
    /*!
     * \brief To find current value of Jump Count
     * \return
     */
    int getJumpCount();
    /*!
     * \brief To set the Value of Jump Count
     */
    void setJumpCount(int);
    /*!
     * \brief To update the Jump State
     */
    void jumpUpdate();
};

#endif // JUMPINGSTATE_H
