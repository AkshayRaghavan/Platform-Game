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
#include "startbutton.h"
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
    QMediaPlayer * bg = new QMediaPlayer();
    QFileInfo file("resources/game files/bg.mp3");
    //bg->setMedia(QUrl("file://resources/game files/bg.mp3"));
    bg->setMedia(QUrl("file://"+file.absoluteFilePath()));
    bg->play();


    QGraphicsScene *scene = new QGraphicsScene();
    InputHandler* view_global = new InputHandler(NULL);

    QRect rec = QApplication::desktop()->availableGeometry();
    int screen_initial_height = rec.height() - 2*view_global->frameWidth() - QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    int screen_initial_width = screen_initial_height * 1.5;

    view_global->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_global->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_global->setFixedSize(screen_initial_width, screen_initial_height);     //1000 : width (X Axis) , 800 : height (Y Axis)
    view_global->setSceneRect(0,0,screen_initial_width, screen_initial_height);



    StartButton* start_button = new StartButton(&a , scene , view_global , "PLAY GAME" , milliseconds_per_frame, screen_initial_width, screen_initial_height);
    ExitButton* exit_button = new ExitButton("EXIT");

    QGraphicsProxyWidget * start_proxy = scene->addWidget(start_button);
    start_button->setProxy(start_proxy);
    start_proxy->setPos(500 , 500);

    QGraphicsProxyWidget * end_proxy = scene->addWidget(exit_button);
    start_button->setProxy(end_proxy);
    end_proxy->setPos(500 , 700);

    view_global->setScene(scene);
    view_global->show();
    a.exec();
    return 0;
}
