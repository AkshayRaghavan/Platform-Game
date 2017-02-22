#ifndef READINPUT_H
#define READINPUT_H

#include "gameobject.h"
#include "tile.h"
#include "gem.h"
#include "gamestate.h"
#include<QDebug>
#include<QGraphicsScene>
#include<fstream>

class ReadInput
{
    std::vector<GameObject*> gameObject;
    std::vector< std::vector<Tile*> > tileMap;
    std::vector<Gem*> gems;
    GameState *gameState;
    QGraphicsScene * scene;

    void functionToCreateTileMap(std::string file_path , int size_of_tile , int row_tile_matrix_size , int column_tile_matrix_size);


public:
    ReadInput (QGraphicsScene * scene);
};

#endif // READINPUT_H
