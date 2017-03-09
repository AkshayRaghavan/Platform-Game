#ifndef COMPUTERINPUTCOMPONENT_H
#define COMPUTERINPUTCOMPONENT_H

#include "inputcomponent.h"

//! The input component to handle state changes for non human input
/*!
 * This is handles state changes for all the monsters and updates them as needed
*/

class ComputerInputComponent : public InputComponent
{
public:
    /*!
     * \brief Constructor
     */
    ComputerInputComponent() {}

    /*!
     * \brief Destructor
     */
    virtual ~ComputerInputComponent() {}

    /*!
     * \brief Updates the state of the corresponding GameObject
     * \param gameObject the GameObject whose state will be updated
     */
    virtual void update(GameObject &gameObject);

    /*!
     * \brief Checks whether the GameObject accepts input
     * \return false, as GameObject with ComputerInputComponent does not accept input
     */
    virtual bool acceptsInput();
};

#endif // COMPUTERINPUTCOMPONENT_H
