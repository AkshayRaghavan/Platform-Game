#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include <QPen>
#include <QGraphicsScene>

// A class for a tile rectangle
// Used for stopping player on obstacle detection

/*!
 * \brief The Class to Make Tiles
 */

class Tile : public QGraphicsRectItem
{
private:
    /*!
     * \brief To store whether Tile is an obstacle
     */
    bool isObstacle;
    /*!
     * \brief To store it's x coordinate
     */
    qreal columnPosition;
    /*!
     * \brief To store it's y coordinate
     */
    qreal rowPosition;
    /*!
     * \brief To store Width of Tile
     */
    qreal widthOfTile;
    /*!
     * \brief To store Height of Tile
     */
    qreal heightOfTile;
    /*!
     * \brief A QGraphicsRectItem to make the Tile
     */
    QGraphicsRectItem* r;
public:
    /*!
     * \brief Constructor For Tile Class
     * \param scene The pointer to the Scene where to add the Tile
     * \param column The x Coordinate of The Tile
     * \param row The y Coordinate of the Tile
     * \param width Widthh of the Tile
     * \param height Width of the Tile
     * \param is_obstacle To see if it's an obstacle
     */
    Tile(QGraphicsScene * scene , qreal column , qreal row , qreal width , qreal height , bool is_obstacle);
    /*!
     * \brief Function to get the pointer to the Tile
     * \return Returns the pointer to the Tile
     */
    QGraphicsRectItem* getR();
    /*!
     * \brief Function to check if it's obstacle
     * \return Returns the value of isObstacle
     */
    bool getIsObstacle();
    /*!
     * \brief Function to return width of Tile
     * \return Width of Tile
     */
    qreal getWidthOfTile();
    /*!
     * \brief Fucntion to return height of Tile
     * \return Height of Tile
     */
    qreal getHeightOfTile();

};

#endif // TILE_H
