#include "gamestate.h"

GameState::GameState(std::vector<GameObject*> &game_objects, std::vector< std::vector<Tile*> > &tile_map, std::vector<Gem*> &input_gems) :
    gameObjects(game_objects), tileMap(tile_map), gems(input_gems)
{

}

QGraphicsScene *GameState::getScene()
{
    return scene;
}

std::vector<GameObject*> GameState::getGameObjects()
{
    return gameObjects;
}

std::vector<std::vector<Tile*> > GameState::getTileMap()
{
    return tileMap;
}

std::vector<Gem*> GameState::getGems()
{
    return gems;
}

void GameState::update()
{
    for(int i=0; i<gameObjects.size(); i++)
    {
        if(gameObjects[i]->isAcceptingInput())
        {
            gameObjects[i]->physicsComponent->update();
            gameObjects[i]->graphicsComponent->update();
        }
        else
        {
            gameObject[i]->inputComponent->update();
            gameObjects[i]->physicsComponent->update();
            gameObjects[i]->graphicsComponent->update();
        }
    }
}




