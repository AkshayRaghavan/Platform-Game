#ifndef GEM_H
#define GEM_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <mutex>

/*!
 * \brief Describes a Gem
 * Describes a Gem, an object that can be captured by players to earn points.
 * Handles the drawing, placement, update, and score of the gems
 */

class Gem : public QGraphicsPixmapItem
{
private:
    /*!
     * \brief Specifies whether the gem is on the screen, used by the server
     */
    bool isOnScreen;

    /*!
     * \brief Specifies whether the gem is not on the screen, used by the client
     */
    bool removedFromScreen;

    /*!
     * \brief Specifies the points given to the player capturing the gem
     */
    int pointValue;

    /*!
     * \brief Mutex to protect the capture of the game, so that multiple players do not capture concurrently
     */
    std::mutex protectGem;
public:
    /*!
     * \brief Draws the Gem on the scene
     * \param scene_input the scene on which the Gem is drawn
     */
    virtual void drawGem(QGraphicsScene *scene_input) {}

    /*!
     * \brief Get the score given to the player on capture of the Gem
     * \return the value of the score
     */
    int getPointValue();

    /*!
     * \brief Get if player is not on the screen in the client
     * \return true, if not on the screen, false, otherwise
     */
    bool getRemovedFromScreen();

    /*!
     * \brief Set whether the Gem is not on the screen in the client
     * \param input the value to set
     */
    void setRemovedFromScreen(bool input);

    /*!
     * \brief Get if the Gem is on the screen in the server
     * \return true, if yes, false, if not
     */
    bool getIsOnScreen();

    /*!
     * \brief Set whether the Gem is in the screen in the server
     * \param input the value to set
     */
    void setIsOnScreen(bool input);

    /*!
     * \brief Set the number of points a player capturing the Gem would receive
     * \param input the value of the number of points
     */
    void setPointValue(int input);

    /*!
     * \brief Removes the Gem from the scene
     * \param input_scene the scene from which the Gem is to be removed
     */
    void remove(QGraphicsScene* input_scene);
};

#endif // GEM_H
