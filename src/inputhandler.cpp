#include "inputhandler.h"
#include "gameobject.h"
#include <QEvent>
#include <QDebug>
void InputHandler::keyPressEvent(QKeyEvent *event)
{
    if(gameState && gameState->remoteIdentity == enumerator::Identity::CLIENT )
    {
        std::vector<GameObject*> gameObjects = (this->gameState)->getGameObjects();
        QKeyEvent *key_event = dynamic_cast<QKeyEvent*>(event);
        if(!key_event)
        {
            return;
        }
        else
        {
                QJsonObject object;
                object.insert ("arrayIndex" , QJsonValue(clientPtr->getArrayIndex()));
                object.insert ("eventName" , QJsonValue("keypress"));
                            
                switch (event->key()) {
                    case Qt::Key_Up: object.insert ("key" , QJsonValue("UP")); break;
                    case Qt::Key_Left: object.insert ("key" , QJsonValue("LEFT")); break;
                    case Qt::Key_Right: object.insert ("key" , QJsonValue("RIGHT")); break;
                    default : return ;
                }
                QJsonDocument doc(object);
                QByteArray bytes = doc.toJson();
                (clientPtr->getClientWebSocket())->sendBinaryMessage(bytes);
        }
    }
}


void InputHandler::keyReleaseEvent(QKeyEvent *event)
{
    if(gameState && gameState->remoteIdentity == enumerator::Identity::CLIENT )
    {
        std::vector<GameObject*> gameObjects = (this->gameState)->getGameObjects();
        QKeyEvent *key_event = dynamic_cast<QKeyEvent*>(event);
        if(!key_event)
        {
            return;
        }
        else
        {
                QJsonObject object;
                object.insert ("arrayIndex" , QJsonValue(clientPtr->getArrayIndex()));
                object.insert ("eventName" , QJsonValue("keyrelease"));
                            
                switch (event->key()) {
                    case Qt::Key_Up: object.insert ("key" , QJsonValue("UP")); break;
                    case Qt::Key_Left: object.insert ("key" , QJsonValue("LEFT")); break;
                    case Qt::Key_Right: object.insert ("key" , QJsonValue("RIGHT")); break;
                    default : return ;
                }
                QJsonDocument doc(object);
                QByteArray bytes = doc.toJson();
                (clientPtr->getClientWebSocket())->sendBinaryMessage(bytes);
        }
    }
}

void InputHandler::setGameClient(Client *x)
{
    clientPtr = x;
}

void InputHandler::setGameState(GameState *x)
{
    gameState = x;
}
InputHandler::InputHandler(GameState *input_game_state)
{
    gameState = input_game_state;
}
