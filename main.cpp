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
#include <QDesktopWidget>
#include <QStyle>
#include <QMediaPlayer>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    int milliseconds_per_frame = 50;
    QApplication a(argc, argv);
    QGraphicsScene *scene = new QGraphicsScene;
    ReadInput readInput(scene);
    GameState * gameState = readInput.createGameStateObject("resources/game files/tile map level1/tile map level1.txt" , "resources/game files/gems/diamond map level1.txt" , "resources/game files/player/player1 level1.txt" , "resources/game files/player/player2 level1.txt" , "resources/game files/monster/monster level1.txt" , "resources/game files/fire/fire level1.txt" , "resources/game files/door/door.txt", milliseconds_per_frame);

    InputHandler *view = new InputHandler(gameState);
//    gameState->installEventFilter(view); //set focus?
 //   QGraphicsView *view = new QGraphicsView;
    view->setScene(gameState->getScene());
    QMediaPlayer * bg = new QMediaPlayer();
    QFileInfo file("resources/game files/bg.mp3");
    //bg->setMedia(QUrl("file://resources/game files/bg.mp3"));
    bg->setMedia(QUrl("file://"+file.absoluteFilePath()));
    bg->play();

    QImage *back = new QImage("resources/images/bg2.png");
    QImage *background = new QImage(back->scaled(gameState->screenWidth,gameState->screenHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation));
    QBrush *brush = new QBrush(*background);
    view->setBackgroundBrush(*brush);
    //view->setBackgroundBrush(QImage("resources/images/bg2.png"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    qDebug() << gameState->screenWidth;
    qDebug() << gameState->screenHeight;

   // inputHandler->setFocus();
    view->setFixedSize(gameState->screenWidth,gameState->screenHeight+QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight));     //1000 : width (X Axis) , 800 : height (Y Axis)
    view->setSceneRect(0,0,gameState->screenWidth,gameState->screenHeight+QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight));
    view->show();

    QRect rec = QApplication::desktop()->availableGeometry();

    qDebug() <<  rec.width()<< rec.height();

    QTimer * timer = new QTimer();

    gameState->connect(timer,SIGNAL(timeout()),gameState,SLOT(update()));
    timer->start(50);

    return a.exec();
}


/*

files in readinput.cpp



player 1 :
*/
