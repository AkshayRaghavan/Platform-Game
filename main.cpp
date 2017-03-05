#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include <QEvent>
#include <QDebug>
#include "server.h"
#include "readinput.h"
#include "gamestate.h"
#include "gameobject.h"
//#include "inputhandler.h"
#include <QDesktopWidget>
//#include "startbutton.h"
#include "exitbutton.h"
#include<QGraphicsScene>
#include<QGraphicsProxyWidget>
#include <QStyle>
#include <QMediaPlayer>
#include <QFileInfo>

int main(int argc, char *argv[])
{

    int milliseconds_per_frame = 50;
    QApplication a(argc, argv);

    //   gameState->installEventFilter(view); //set focus?
    //   QGraphicsView *view = new QGraphicsView;
    //   QMediaPlayer * bg = new QMediaPlayer();
    //  QFileInfo file("resources/game files/bg.mp3");
    //bg->setMedia(QUrl("file://resources/game files/bg.mp3"));
    // bg->setMedia(QUrl("file://"+file.absoluteFilePath()));
    // bg->play();


    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView();

    QRect rec = QApplication::desktop()->availableGeometry();
    int screen_initial_height = rec.height() - 2*view->frameWidth() - QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    int screen_initial_width = screen_initial_height * 1.5;
    Server game_server(3000 , scene , screen_initial_width , screen_initial_height , milliseconds_per_frame);
    a.exec();
    return 0;
}
