#include "inputhandler.h"
#include "gameobject.h"
#include <QEvent>


bool InputHandler::eventFilter(QObject *watched, QEvent *event)
{
    std::vector<GameObject*> gameObjects = (this->gameState)->getGameObjects();
    QKeyEvent *key_event = dynamic_cast<QKeyEvent*>(event);
    if(!key_event)
    {
        return false;
    }
    for(int i = 0; i < gameObjects.size(); i++)
    {
        if( (gameObjects[i]->GameObject::isAcceptingInput()) && (gameObjects[i]->inputComponent->keys)->find(static_cast<Qt::Key> (key_event->key())))
        {
            QCoreApplication::postEvent(gameObjects[i],event);
            return true;
        }
    }
    return false;
}

InputHandler::InputHandler(GameState *input_game_state)
{
    gameState = input_game_state;
}
