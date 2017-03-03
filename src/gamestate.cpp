#include "gamestate.h"
#include <QObject>

GameState::GameState(std::vector<GameObject*> &game_objects, std::vector< std::vector<Tile*> > &tile_map, std::vector<Gem*> &input_gems , int screen_width , int screen_height , QGraphicsScene* scene, int milliseconds_per_frame, int total_time_available) :
    gameObjects(game_objects), tileMap(tile_map), gems(input_gems) ,
    screenWidth(screen_width) , screenHeight(screen_height) ,
    scene(scene)
{
    isGameRunning = true;
    timer = new Timer(total_time_available,milliseconds_per_frame);
   // timer->setPlainText(timer->getTimeLeft().c_str());
   // timer->setFont(QFont("Helvetica" , 55));
   // timer->setDefaultTextColor(QColor(51, 51, 255));
   // timer->setPos(50 , 50);
   //scene->addItem(timer);
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
    for(unsigned int i=0; i<gameObjects.size(); i++)
    {
        if(gameObjects[i]->isAcceptingInput() && !(gameObjects[i]->getIsDead()))
        {
            someone_accepting_input = true;
            //(gameObjects[i]->graphicsComponent)->update(*gameObjects[i]);
            (gameObjects[i]->physicsComponent)->update(*gameObjects[i]);
           // if(gameObjects[i]->scoreComponent)
            //    (gameObjects[i]->scoreComponent)->update(gameObjects[i]->getScore());
        }
        else
        {
            (gameObjects[i]->inputComponent)->update(*gameObjects[i]);
           // (gameObjects[i]->graphicsComponent)->update(*gameObjects[i]);
            (gameObjects[i]->physicsComponent)->update(*gameObjects[i]);
            //if(gameObjects[i]->scoreComponent)
            //    (gameObjects[i]->scoreComponent)->update(gameObjects[i]->getScore());
        }
    }
    timer->update();
    if(!someone_accepting_input || !(timer->isTimeLeft()))
    {
        isGameRunning = false;
    }
}




