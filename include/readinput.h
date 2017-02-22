#ifndef READINPUT_H
#define READINPUT_H

#include "gameobject.h"
#include "tile.h"
#include "gem.h"
#include "gamestate.h"


class ReadInput
{
    std::vector<GameObject*> gameObject;
    std::vector< std::vector<Tile*> > tileMap;
    std::vector<Gem*> gems;
    GameState *gameState;



};

#endif // READINPUT_H
