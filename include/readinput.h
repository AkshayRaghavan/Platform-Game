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

class ReadInput
{

public:
    enumerator::Identity remoteIdentity;
    std::vector<GameObject*> gameObject;
    std::vector< std::vector<Tile*> > tileMap;
    std::vector<Gem*> gems;
    QGraphicsScene * scene;
    qreal width_of_tile;
    qreal height_of_tile;
    QApplication * app;
    int screenWidth;
    int screenHeight;
    int totalTime;

    ReadInput (QGraphicsScene * scene, int screen_width, int screen_height);
    ~ReadInput();
    void functionToCreateTileMap(std::string file_path);
    void functionToCreateGem(std::string file_path);
    void functionToCreatePlayerGameObject(std::string);
    void functionToCreateMonsterGameObject(std::string );
    void functionToCreateFireObject(std::string );
    void functionToCreateDoor(std::string );
    void setApp(QApplication *a);

};

#endif // READINPUT_H













