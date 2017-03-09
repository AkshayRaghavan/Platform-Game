#ifndef READINPUT_H
#define READINPUT_H
#include"enumerator.h"
#include "gameobject.h"
#include "tile.h"
#include "gem.h"
#include "diamond.h"
#include "gamestate.h"
#include "inputcomponent.h"
#include "humaninputcomponent.h"
#include "computerinputcomponent.h"
#include "graphicscomponent.h"
#include "scorecomponent.h"
#include "playergraphicscomponent.h"
#include "firegraphicscomponent.h"
#include "keys.h"
#include "physicscomponent.h"
#include "playerphysicscomponent.h"
#include "monsterphysicscomponent.h"
#include "emptyinputcomponent.h"
#include "emptyphysicscomponent.h"
#include "door.h"
#include "stopleft.h"
#include "stopright.h"
#include<QDebug>
#include<QGraphicsScene>
#include<QKeySequence>
#include <vector>
#include <QString>
#include<fstream>
#include <thread>
#include <QApplication>

/*!
 * \brief Function to read input from the game files
 */

class ReadInput
{

public:
    /*!
     * \brief Stores whether it is Server or Client
     */
    enumerator::Identity remoteIdentity;
    /*!
     * \brief Vector Containing all the Game Objects
     */
    std::vector<GameObject*> gameObject;
    /*!
     * \brief The Tile Map Vector
     */
    std::vector< std::vector<Tile*> > tileMap;
    /*!
     * \brief vector to store all the gems
     */
    std::vector<Gem*> gems;
    /*!
     * \brief The Scene where to add all the game objects
     */
    QGraphicsScene * scene;
    /*!
     * \brief Width of the Tile relative to Screen Width
     */
    qreal width_of_tile;
    /*!
     * \brief Height of the Tile relative to Screen Height
     */
    qreal height_of_tile;
    /*!
     * \brief QApplication
     */
    QApplication * app;
    /*!
     * \brief Width of the Screen
     */
    int screenWidth;
    /*!
     * \brief Height of the Screen
     */
    int screenHeight;
    /*!
     * \brief Total Time before Game Ends
     */
    int totalTime;

    /*!
     * \brief Constructor
     * \param scene The Scene pointer
     * \param screen_width Value of Width of Screen
     * \param screen_height Value of Height of Screen
     */
    ReadInput (QGraphicsScene * scene, int screen_width, int screen_height);
    /*!
     * \brief Destructor
     */
    ~ReadInput();
    /*!
     * \brief Function to Create the Tile Map
     * \param file_path Path of File containing information of Tile Map
     */
    void functionToCreateTileMap(std::string file_path);
    /*!
     * \brief Function to Create Gems
     * \param file_path Path of the File containing information about Gems
     */
    void functionToCreateGem(std::string file_path);
    /*!
     * \brief Function to Create The Players
     * \param file_path Path of the File containing all the information about players
     */
    void functionToCreatePlayerGameObject(std::string file_path);
    /*!
     * \brief Function to Create the Monsters
     * \param file_path Path of the File Containing monsters
     */
    void functionToCreateMonsterGameObject(std::string file_path );
    /*!
     * \brief Function to Create Fire
     * \param fire_file_path Path of the File containing Fire
     */
    void functionToCreateFireObject(std::string fire_file_path );
    /*!
     * \brief functionToCreateDoor
     * \param door_file_path Path of the File containing Door information
     */
    void functionToCreateDoor(std::string door_file_path );
    /*!
     * \brief To set the Current QApplication
     * \param QApplication Pointer
     */
    void setApp(QApplication *a);

};

#endif // READINPUT_H













