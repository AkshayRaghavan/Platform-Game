#ifndef HUMANINPUTCOMPONENT_H
#define HUMANINPUTCOMPONENT_H

#include "inputcomponent.h"
#include <QEvent>
#include <Qt>
#include <set>

/*!
 * \brief Component of GameObject that handles human input
 * Handles keyboard input (key press and key release) events and updates the State of the GameObject
 */

class HumanInputComponent : public InputComponent
{
    /*!
     * \brief Set of keys currently pressed
     */
    std::set<Qt::Key> keysPressed;
public:

    /*!
     * \brief Constructor
     * \param keys Specify the keys for jump, left, and right
     */
    HumanInputComponent(Keys *keys);

    /*!
     * \brief Destructor
     */
    virtual ~HumanInputComponent() {}

    /*!
     * \brief Updates the InputComponent of gameObject
     * \param gameObject the gameObject to be updated
     */
    virtual void update(GameObject &gameObject);

    /*!
     * \brief Received keyboard events and updates accordingly
     * \param event the event received
     * \return true, if event is recognized and State updated, false, otherwise
     */
    bool event(QEvent *event);

    /*!
     * \brief Get whether the corresponding GameObject accepts input from th keyboard
     * \return true, as GameObject with HumanInputComponent accepts input
     */
    virtual bool acceptsInput();

};

#endif // HUMANINPUTCOMPONENT_H
