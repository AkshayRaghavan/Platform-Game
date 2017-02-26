#include "gamestate.h"
#include <QObject>
#include <QMetaType>

GameState::GameState(std::vector<GameObject*> &game_objects, std::vector< std::vector<Tile*> > &tile_map, std::vector<Gem*> &input_gems , int screen_width , int screen_height , QGraphicsScene* scene) :
    gameObjects(game_objects), tileMap(tile_map), gems(input_gems) ,
    screenWidth(screen_width) , screenHeight(screen_height) ,
    scene(scene)

{
//    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    isGameRunning = true;
    for(int i = 0;i < game_objects.size();i++)
    {
        connect((game_objects[i])->physicsComponent,SIGNAL(setPosition(GameObject &,QPointF &)),this,SLOT(setPosition(GameObject &,QPointF &)));
        connect((game_objects[i])->physicsComponent,SIGNAL(removeObject(QGraphicsItem &)),this,SLOT(removeObject(QGraphicsItem &)));
        connect((game_objects[i])->graphicsComponent,SIGNAL(setPixMapValue(GraphicsComponent *, QPixmap)),this,SLOT(setPixMapValue(GraphicsComponent *, QPixmap )));
    }
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

/*void GameState::update()
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
    if(!someone_accepting_input)
    {
        isGameRunning = false;
    }
}*/


void GameState::update()
{
    bool * someone_accepting_input = new bool;
    *someone_accepting_input = false;
    if(!isGameRunning)
    {
        return;
    }
    int size = gameObjects.size();
    std::vector<std::thread> th_array;
    GameObject* temp_ptr;
    for(int i=0; i<size; i++)
    {
        temp_ptr = gameObjects[i];
        th_array.push_back(        std::thread ( [&] (){ parallel( temp_ptr->isAcceptingInput() ,  temp_ptr , someone_accepting_input); }));
    }
    for(int i=0; i<size; i++)
    {
        th_array[i].join();
        if(gameObjects[i]->scoreComponent)
            (gameObjects[i]->scoreComponent)->update(gameObjects[i]->getScore());

    }
    if(!(*someone_accepting_input))
    {
        isGameRunning = false;
    }
}



void GameState::parallel(bool isAcceptingInput , GameObject * player_ptr , bool *someone_accepting_input)
{
    if(isAcceptingInput && !(player_ptr->getIsDead()))
    {
        *someone_accepting_input = true;
        (player_ptr->physicsComponent)->update(*player_ptr);
        (player_ptr->graphicsComponent)->update(*player_ptr);
    }
    else
    {
        (player_ptr->inputComponent)->update(*player_ptr);
        (player_ptr->physicsComponent)->update(*player_ptr);
        (player_ptr->graphicsComponent)->update(*player_ptr);
    }
}

void GameState::setPosition(GameObject &gameObject, QPointF &point)
{
    qDebug() << "setPos slot called";
    gameObject.graphicsComponent->setPos(point);
}

void GameState::setPixMapValue(GraphicsComponent *graphics_component, QPixmap pixMap)
{
    graphics_component->setPixmap(pixMap);
}

void GameState::removeObject(QGraphicsItem &gameObject)
{
    scene->removeItem(&gameObject);
}




