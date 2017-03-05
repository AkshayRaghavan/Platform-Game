#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QCoreApplication>
#include <QEvent>
#include <QKeyEvent>
#include <vector>
#include "inputcomponent.h"
#include "gamestate.h"
#include "keys.h"
#include "client.h"

class Client;

class InputHandler : public QGraphicsView
{
private:
    GameState *gameState;
    Client * clientPtr;
public:
    InputHandler(GameState *);
    void setGameClient(Client *);
    void setGameState(GameState *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // INPUTHANDLER_H
