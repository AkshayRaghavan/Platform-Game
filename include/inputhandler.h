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

class InputHandler : public QGraphicsView
{
private:
    GameState *gameState;
public:
    InputHandler(GameState *);
    void setGameState(GameState *x);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // INPUTHANDLER_H
