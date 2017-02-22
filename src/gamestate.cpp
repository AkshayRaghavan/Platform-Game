#include "gamestate.h"

GameState::GameState(std::vector<GameObject> &game_objects, std::vector< std::vector<Tile> > &tile_map, std::vector<Gem> &input_gems) :
    gameObjects(game_objects), tileMap(tile_map), gems(input_gems)
{

}

QGraphicsScene *GameState::getScene()
{
    return scene;
}

std::vector<GameObject> GameState::getGameObjects()
{
    return gameObjects;
}

std::vector<std::vector<Tile> > GameState::getTileMap()
{
    return tileMap;
}

std::vector<Gem> GameState::getGems()
{
    return gems;
}




