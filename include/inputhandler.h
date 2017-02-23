#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>
#include <QCoreApplication>
#include <QEvent>
#include <QKeyEvent>
#include <vector>
#include "inputcomponent.h"
#include "gamestate.h"
#include "keys.h"

class InputHandler : public QObject
{
private:
    GameState *gameState;
public:
    InputHandler(GameState *);
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // INPUTHANDLER_H
