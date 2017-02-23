#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include <QEvent>
#include <QDebug>
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
    qDebug() << "start\n";
    GameState * gameState = readInput.createGameStateObject("resources/game files/tile map level1/tile map level1.txt" , "resources/game files/gems/diamond map level1.txt" , "resources/game files/player/player1 level1.txt" , "resources/game files/player/player2 level1.txt" , "resources/game files/monster/monster level1.txt");
    qDebug() << "end";

    InputHandler *inputHandler = new InputHandler(gameState);
    gameState->installEventFilter(inputHandler); //set focus?
    QGraphicsView *view = new QGraphicsView;
    view->setScene(gameState->getScene());
    view->setBackgroundBrush(QImage("resources/images/bg2.png"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    qDebug() << gameState->screenWidth;
    qDebug() << gameState->screenHeight;


    view->setFixedSize(gameState->screenWidth,gameState->screenHeight);     //1000 : width (X Axis) , 800 : height (Y Axis)
    view->setSceneRect(0,0,gameState->screenWidth,gameState->screenHeight);
    view->show();
    QObject::connect(timer,SIGNAL(timeout()),gameState,SLOT(gameState.update()));

    return a.exec();
}


/*

files in readinput.cpp



player 1 :
*/
