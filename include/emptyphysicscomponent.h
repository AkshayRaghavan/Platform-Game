#ifndef EMPTYPHYSICSCOMPONENT_H
#define EMPTYPHYSICSCOMPONENT_H

#include "physicscomponent.h"

/*!
 * \brief PhysicsComponent for GameObjects that do not move
 * Used for objects such as Fire
 */

class EmptyPhysicsComponent : public PhysicsComponent
{
public:
    /*!
     * \brief Constructor
     */
    EmptyPhysicsComponent() {}

    /*!
     * \brief Destructor
     */
    virtual ~EmptyPhysicsComponent() {}

    /*!
     * \brief Updates the position of gameObject
     * \param gameObject the GameObject whose position is to be updated
     */
    void update(GameObject &gameObject);
};

#endif // EMPTYPHYSICSCOMPONENT_H
