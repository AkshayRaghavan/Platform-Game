#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

class GameObject;
#include "tile.h"
#include <QGraphicsScene>

/*!
 * \brief Component that governs the physics handling of the GameObject
 * Handles the movement of the GameObject, and sets the position on the scene based on the State
 */

class PhysicsComponent : public QObject
{
protected:
    /*!
     * \brief Stores the tile map of the game
     */
    std::vector<std::vector<Tile*> > tilesMap;

    /*!
     * \brief Stores the scene of the game
     */
    QGraphicsScene * scene;

    /*!
     * \brief Width of a tile in the tile map
     */
    qreal width_of_tile;

    /*!
     * \brief Height of a tile in the tile map
     */
    qreal height_of_tile;

    /*!
     * \brief Width of the window in which the game runs
     */
    qreal screenWidth;

    /*!
     * \brief Height of the window in which the game runs
     */
    qreal screenHeight;

    /*!
     * \brief Stores the number of frames more the object will move up when jumping
     */
    int curJumpCount;

    /*!
     * \brief Stores the total number of tiles the object moves up when jumping
     */
    int maxJumpCount;
public:
    /*!
     * \brief Constructor
     */
    PhysicsComponent() {}

    /*!
     * \brief Destructor
     */
    virtual ~PhysicsComponent() {}

    /*!
     * \brief Updates the GameObject object's position based on State
     */
    virtual void update (GameObject &) = 0;

    /*!
     * \brief Checks whether it is valid for GameObject to be at point
     * \param point the point to be checked
     * \return true, if valid position in tile map free of obstacles, false otherwise
     */
    bool inRange(QPointF point);

    /*!
     * \brief Checks whether it is valid for GameObject to be at point
     * \param point the point to be checked
     * \return true, if valid position in tile map free of obstacles, false otherwise
     */
    bool testPoint(QPointF point);

    /*!
     * \brief Check if a GameObject can be placed at point such that all the points it covers are valid
     * \param input_point the point to be checked
     * \param player_width the width of the GraphicsComponent of the GameObject
     * \param player_height the height of the GraphicsComponent of the GameObject
     * \return true, if valid position in tile map free of obstacles, false otherwise
     */
    bool testPositionForPlayer(QPointF input_point, qreal player_width, qreal player_height);

    /*!
     * \brief Check whether gameObject would start falling
     * \param gameObject the GameObject to test on
     * \return true if not, false otherwise
     */
    bool hasNoPlatformUnder(GameObject &gameObject);

    /*!
     * \brief Check whether gameObject has an obstacle right in front of it
     * \param gameObject the GameObject to test on
     * \return true if yes, false otherwise
     */
    bool hasObstacleInFront(GameObject &gameObject);
};

#endif // PHYSICSCOMPONENT_H
