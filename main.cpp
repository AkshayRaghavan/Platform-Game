#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include "readinput.h"
#include "gamestate.h"
#include "gameobject.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimer *timer = new QTimer;
    timer->setInterval(1000/33);
    QGraphicsScene *scene = new QGraphicsScene;
    ReadInput readInput(scene);
    GameState *gameState = readInput.createGameStateObject();
    QGraphicsView *view = new QGraphicsView;
    view->setScene(gameState->getScene());
    view->show();
    connect(timer,SIGNAL(timeout()),gameState,SLOT(update()));
    return a.exec();
}


/*

files in readinput.cpp



player 1 :
*/
