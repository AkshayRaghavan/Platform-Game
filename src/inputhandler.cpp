#include "inputhandler.h"
#include "gameobject.h"
#include <QEvent>
#include <QDebug>


void InputHandler::keyPressEvent(QKeyEvent *event)
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
    //        qDebug() << "posting event";
            QCoreApplication::sendEvent(gameObjects[i],event);
        }
    }
}

void InputHandler::keyReleaseEvent(QKeyEvent *event)
{
 //    qDebug() << "received event in event filter";
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
        //    qDebug() << "posting event";
            QCoreApplication::sendEvent(gameObjects[i],event);
        }
    }
}

InputHandler::InputHandler(GameState *input_game_state)
{
    gameState = input_game_state;
}
