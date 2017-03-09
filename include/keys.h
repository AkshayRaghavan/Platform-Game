#ifndef KEYS_H
#define KEYS_H

#include <Qt>

/*!
 * \brief Keys that correspond to different movements of the GameObject
 * Stores keys for jump, left, and right movements
 */

class Keys
{
public:

    /*!
     * \brief Key corresponding to jumping
     */
    Qt::Key jump;

    /*!
     * \brief Key corresponding to moving right
     */
    Qt::Key right;

    /*!
     * \brief Key corresponding to moving left
     */
    Qt::Key left;

    /*!
     * \brief Constructor
     * \param jump_input key for jumping
     * \param right_input key for moving right
     * \param left_input key for moving left
     */
    Keys(Qt::Key jump_input, Qt::Key right_input, Qt::Key left_input);

    /*!
     * \brief Check if a given key belongs to the set of keys
     * \param find_key the key to be checked
     * \return true, if yes, false, if no
     */
    bool find(Qt::Key find_key);
};

#endif // KEYS_H
