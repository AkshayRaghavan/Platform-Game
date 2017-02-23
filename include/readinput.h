#ifndef READINPUT_H
#define READINPUT_H

#include "gameobject.h"
#include "tile.h"
#include "gem.h"
#include "diamond.h"
#include "gamestate.h"
#include "inputcomponent.h"
#include "humaninputcomponent.h"
#include "computerinputcomponent.h"
#include "graphicscomponent.h"
#include "playergraphicscomponent.h"
#include "keys.h"
#include<QDebug>
#include<QGraphicsScene>
#include<QKeySequence>
#include <vector>
#include <QString>
#include<fstream>

class ReadInput
{
    std::vector<GameObject*> gameObject;
    std::vector< std::vector<Tile*> > tileMap;
    std::vector<Gem*> gems;
    GameState *gameState;
    QGraphicsScene * scene;

    void functionToCreateTileMap(std::string file_path , int size_of_tile , int row_tile_matrix_size , int column_tile_matrix_size);
    void functionToCreateGem(std::string file_path);
    void functionToCreatePlayerGameObject(std::string file_path , Qt::Key jump_input, Qt::Key right_input, Qt::Key left_input);
    void functionToCreateMonsterGameObject(std::string file_path);

public:
    ReadInput (QGraphicsScene * scene);
};

#endif // READINPUT_H
