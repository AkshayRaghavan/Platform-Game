#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>
#include <QEvent>
#include "gamestate.h"

class InputHandler : public QObject
{
private:
    GameState *gameState;
public:
    InputHandler(GameState *);
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // INPUTHANDLER_H
