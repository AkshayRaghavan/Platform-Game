#include "inputhandler.h"
#include "gameobject.h"
#include <QEvent>
#include <QDebug>


void InputHandler::keyPressEvent(QKeyEvent *event)
{
    if(gameState)
    {
        std::vector<GameObject*> gameObjects = (this->gameState)->getGameObjects();
        QKeyEvent *key_event = dynamic_cast<QKeyEvent*>(event);
        if(!key_event)
        {
            return;
        }
        for(int i = 0; i < gameObjects.size(); i++)
        {
            if( (gameObjects[i]->GameObject::isAcceptingInput()) && (gameObjects[i]->inputComponent->keys)->find(static_cast<Qt::Key> (key_event->key())))
            {
                 QCoreApplication::sendEvent(gameObjects[i],event);
            }
        }
    }
}

void InputHandler::keyReleaseEvent(QKeyEvent *event)
{
    if(gameState)
    {
        std::vector<GameObject*> gameObjects = (this->gameState)->getGameObjects();
        QKeyEvent *key_event = dynamic_cast<QKeyEvent*>(event);
        if(!key_event)
        {
            return;
        }
        for(unsigned int i = 0; i < gameObjects.size(); i++)
        {
            if( (gameObjects[i]->GameObject::isAcceptingInput()) && (gameObjects[i]->inputComponent->keys)->find(static_cast<Qt::Key> (key_event->key())))
            {
                 QCoreApplication::sendEvent(gameObjects[i],event);
            }
        }
    }
}
void InputHandler::setGameState(GameState *x)
{
    gameState = x;
}
InputHandler::InputHandler(GameState *input_game_state)
{
    gameState = input_game_state;
}
