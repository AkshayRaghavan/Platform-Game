#ifndef MONSTERPHYSICSCOMPONENT_H
#define MONSTERPHYSICSCOMPONENT_H

#include "physicscomponent.h"
#include "gameobject.h"
#include "tile.h"
#include <vector>

/*!
 * \brief Component to handle the physics for monster GameObject objects
 * Handles movement and position update of monsters based on State
 */

class MonsterPhysicsComponent : public PhysicsComponent
{
private:
    /*!
     * \brief number of frames to wait before the monster can move
     */
    int curSpeedFraction;

    /*!
     * \brief fraction of number of frames the monster moves for every game frame
     */
    int maxSpeedFraction;
public:

    /*!
     * \brief Constructor
     * \param Tilesmap the tile map of the game
     * \param theight height of a tile
     * \param twidth width of a tile
     * \param sheight height of the screen
     * \param swidth width of the screen
     * \param fraction_of_speed fraction of total frames the monster moves
     */
    MonsterPhysicsComponent(std::vector< std::vector<Tile*> > &Tilesmap, qreal theight, qreal twidth, qreal sheight, qreal swidth, int fraction_of_speed);

    /*!
     * \brief Destructor
     */
    virtual ~MonsterPhysicsComponent() {}

    /*!
     * \brief Update the position of the monster based on State and surroundings
     * \param gameObject the GameObject of the monster
     */
    void update(GameObject &gameObject);
};

#endif // MONSTERPHYSICSCOMPONENT_H
