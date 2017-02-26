#include "gamestate.h"
#include <QObject>

GameState::GameState(std::vector<GameObject*> &game_objects, std::vector< std::vector<Tile*> > &tile_map, std::vector<Gem*> &input_gems , int screen_width , int screen_height , QGraphicsScene* scene, int milliseconds_per_frame, int total_time_available) :
    gameObjects(game_objects), tileMap(tile_map), gems(input_gems) ,
    screenWidth(screen_width) , screenHeight(screen_height) ,
    scene(scene)

{
//    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    isGameRunning = true;
    timer = new Timer(total_time_available,milliseconds_per_frame);
}

QGraphicsScene * GameState::getScene()
{
    return scene;
}

bool GameState::isGameActive()
{
    return isGameRunning;
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

/*void GameState::setTimerAndConnect(QTimer *timer)
{
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(update()));
}*/

void GameState::update()
{
    bool someone_accepting_input = false;
    if(!isGameRunning)
    {
        return;
    }
    for(int i=0; i<gameObjects.size(); i++)
    {
        if(gameObjects[i]->isAcceptingInput() && !(gameObjects[i]->getIsDead()))
        {
            someone_accepting_input = true;
            gameObjects[i]->physicsComponent->update(*gameObjects[i]);
            gameObjects[i]->graphicsComponent->update(*gameObjects[i]);
        }
        else
        {
            gameObjects[i]->inputComponent->update(*gameObjects[i]);
            gameObjects[i]->physicsComponent->update(*gameObjects[i]);
            gameObjects[i]->graphicsComponent->update(*gameObjects[i]);
        }
    }
    timer->update();
    if(!someone_accepting_input || !(timer->isTimeLeft()))
    {
        isGameRunning = false;
    }
}




