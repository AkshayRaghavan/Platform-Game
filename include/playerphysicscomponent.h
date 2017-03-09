#ifndef PLAYERPHYSICSCOMPONENT_H
#define PLAYERPHYSICSCOMPONENT_H

#include "physicscomponent.h"
#include "playergraphicscomponent.h"
#include "firegraphicscomponent.h"
#include "enumerator.h"
#include "state.h"
#include "jumpingstate.h"
#include "gameobject.h"
#include "tile.h"
#include "door.h"
#include "stopleft.h"
#include "stopright.h"
#include <QGraphicsScene>
#include <QMediaPlayer>

/*!
 * \brief Component to handle the physics of a GameObject that is a player
 * Handles movement and sets position of the GameObject based on its State
 */

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
    /*!
     * \brief Constructor
     * \param Tilesmap the tile map of the game
     * \param theight height of a tile
     * \param twidth width of a tile
     * \param sheight height of the window in which the game is played
     * \param swidth width of the window in which the game is played
     * \param scene scene of the game
     */
    PlayerPhysicsComponent(std::vector<std::vector<Tile*> > &Tilesmap, qreal theight, qreal twidth, qreal sheight, qreal swidth, QGraphicsScene * scene);

    /*!
     * \brief Updates the positions of the GameObject based on the State
     * \param gameObject the GameObject to be updated
     */
    void update(GameObject &gameObject);
};

#endif // PLAYERPHYSICSCOMPONENT_H
