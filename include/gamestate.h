#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <QObject>
#include <QGraphicsScene>
#include "threadpool.h"
#include "gameobject.h"
#include "tile.h"
#include "gem.h"
#include "timer.h"

/*!
 * \brief The state of the Game
 * Stores the state of the game. Stores all the GameObject members, Gem members, tile map, and handles update of state
 */

class GameState : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief pool of threads to use for updating the GameState
     */
    ThreadPool threadPool;

    /*!
     * \brief Specifies whether the object resides in a client or a server
     */
    enumerator::Identity remoteIdentity;

    /*!
     * \brief Specifies whether the game is running
     */
    bool isGameRunning;

    /*!
     * \brief Constructor
     * \param game_objects vector of GameObject in the game
     * \param tile_map 2D vector of tiles for the game
     * \param input_gems vector of Gem
     * \param screen_width width of the screen
     * \param screen_height height of the screen
     * \param scene_local scene where the game is displayed
     * \param milliseconds_per_frame the time interval in which the frame is changed
     * \param total_time_available the total time available to play the game
     */
    GameState(std::vector<GameObject*> &game_objects, std::vector< std::vector<Tile*> > &tile_map, std::vector<Gem*> &input_gems , int screen_width , int screen_height , QGraphicsScene* scene_local, int milliseconds_per_frame, int total_time_available);

    /*!
     * \brief Destructor
     */
    virtual ~GameState(){}

    /*!
     * \brief Stores pointers to all the GameObject objects in the game
     */
    std::vector<GameObject*> gameObjects;

    /*!
     * \brief Stores pointers to tiles in the tile map for the game
     */
    std::vector< std::vector<Tile*> > tileMap;

    /*!
     * \brief Stores pointers to all the Gem objects in the game
     */
    std::vector<Gem*> gems;

    /*!
     * \brief Stores the scene in which the game will be displayed
     */
    QGraphicsScene *scene;

    /*!
     * \brief Timer that keeps track of the time left to play the game
     */
    Timer *timer;

    /*!
     * \brief Width of the window in which the game is played
     */
    const int screenWidth;

    /*!
     * \brief Height of the window in which the game is played
     */
    const int screenHeight;

    /*!
     * \brief Get the scene in which the game is being played
     * \return the scene
     */
    QGraphicsScene* getScene();

    /*!
     * \brief Get whether the game is still active
     * \return true, if the game is being played, false, if the game is over
     */
    bool isGameActive();

    /*!
     * \brief Get the list of GameObject objects in the game
     * \return vector of pointers of all the GameObject objects
     */
    std::vector<GameObject*> getGameObjects();

    /*!
     * \brief Get the tile map of the game
     * \return 2D vector of pointers to tiles in the game
     */
    std::vector< std::vector<Tile*> > getTileMap();

    /*!
     * \brief Get the Gem objects in the game
     * \return vector of pointers of all the Gem objects
     */
    std::vector<Gem*> getGems();

public slots:
    /*!
     * \brief Updates the state of the game
     * Calls update on all the GameObject objects, Gem objects, Timer, such that the game moves forward my one frame
     * Called once every frame
     */
    void update();
};

#endif // GAMESTATE_H
