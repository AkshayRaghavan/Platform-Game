#ifndef DIAMOND_H
#define DIAMOND_H

#include "gem.h"
#include <QPixmap>

#define NO_Of_GRAPHICS_STATES 8 ///< number of images for the Pixmap

/*!
 * \brief Describes a Diamond
 * Handles the drawing, placement on screen, and position of a diamond
 */

class Diamond : public Gem
{
private:
    /*!
     * \brief Stores the Pixmap to display the diamond
     */
    QPixmap pixMapImage;
public:
    /*!
     * \brief Create a diamond
     * \param image_location the file path of the images to render the diamond
     * \param width the width of the diamond
     * \param height the height of the diamond
     * \param x_coordinate the x coordinate on the screen
     * \param y_coordinate the y coordinate on the screen
     * \param score_of_gem the score obtained by taking the diamond
     */
    Diamond(std::string image_location , int width , int height , qreal x_coordinate , qreal y_coordinate , int score_of_gem);

    /*!
     * \brief Draws the diamond to the scene
     * \param scene the scene to which the diamond is drawn
     */
    void drawGem(QGraphicsScene* scene);
};

#endif // DIAMOND_H
