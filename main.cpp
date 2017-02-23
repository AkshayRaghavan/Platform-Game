#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include <QEvent>
#include "readinput.h"
#include "gamestate.h"
#include "gameobject.h"
#include "inputhandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimer *timer = new QTimer;
    timer->setInterval(1000/33);
    QGraphicsScene *scene = new QGraphicsScene;
    ReadInput readInput(scene);
    GameState * gameState = readInput.createGameStateObject(":resources/game files/tile/tile map level1.txt" , ":resources/game files/gems/diamond map level1.txt" , ":resources/game files/player/player1 level1.txt" , ":resources/game files/player/player2 level1.txt" , ":resources/game files/monster/monster level1.txt");

    InputHandler *inputHandler = new InputHandler(gameState);
    gameState->installEventFilter(inputHandler); //set focus?
    QGraphicsView *view = new QGraphicsView;
    view->setScene(gameState->getScene());
    view->show();
    QObject::connect(timer,SIGNAL(timeout()),gameState,SLOT(gameState.update()));

    return a.exec();
}


/*

files in readinput.cpp



player 1 :
*/
