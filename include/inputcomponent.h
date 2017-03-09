#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

class GameObject;
#include <QObject>
#include "keys.h"

/*!
 * \brief Component to handle inputs given to the GameObject
 * Handles the accepting of inputs, processes it, and updates the State of the GameObject accordingly
 */

class InputComponent : public QObject
{
public:
    /*!
     * \brief Stores the keys corresponding to the motion of the GameObject
     */
    Keys *keys;

    /*!
     * \brief Constructor
     */
    InputComponent();

    /*!
     * \brief Destructor
     */
    virtual ~InputComponent() {}

    /*!
     * \brief Updates the State of gameObject
     * \param gameObject the GameObject to be updated
     */
    virtual void update(GameObject &gameObject) = 0;

    /*!
     * \brief Receives events, processes it, and calls update accordingly
     * \param event the event received
     * \return true, if the event is recogized and processed, false, otherwise
     */
    virtual bool event(QEvent *event);

    /*!
     * \brief Get whether the corresponding GameObject accepts input from the keyboard
     * \return true, if yes, false, otherwise
     */
    virtual bool acceptsInput() = 0;
};

#endif // INPUTCOMPONENT_H
