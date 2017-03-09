#ifndef STATE_H
#define STATE_H

class GameObject;
class InputComponent;
#include "enumerator.h"
#include <Qt>
#include <set>

/*!
 * \brief Class to Identify the Different States that the Players can be in
 */

class State
{
public:
    /*!
     * \brief Destructor
     */
    virtual ~State() {}
    /*!
     * \brief Virtual Fucntion to update the current state based on keypressevent
     * \return
     */
    virtual State* update(InputComponent *,std::set<Qt::Key>) = 0;
    /*!
     * \brief Provides the Type of State
     * \return enumerator::State::STATE_TYPE
     */
    virtual enumerator::State type() = 0;
};

#endif // STATE_H
