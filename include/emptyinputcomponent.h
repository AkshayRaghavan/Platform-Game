#ifndef EMPTYINPUTCOMPONENT_H
#define EMPTYINPUTCOMPONENT_H

#include "inputcomponent.h"

/*!
 * \brief InputComponent for GameObjects that do not have any state changes
 */

class EmptyInputComponent : public InputComponent
{
public:

    /*!
     * \brief Constructor
     */
    EmptyInputComponent() {}

    /*!
     * \brief Destructor
     */
    virtual ~EmptyInputComponent() {}

    /*!
     * \brief updates the State of gameObject
     * \param gameObject the GameObject whose state is to be updated
     */
    virtual void update(GameObject &gameObject);

    /*!
     * \brief Checks whether the GameObject corresponding to this component accepts input
     * \return false, as the component is empty
     */
    virtual bool acceptsInput();
};

#endif // EMPTYINPUTCOMPONENT_H
