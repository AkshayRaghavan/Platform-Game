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
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QRect rec = QApplication::desktop()->availableGeometry();
    int screen_initial_height = rec.height() - 50;
    int screen_initial_width = screen_initial_height * 1.5;

    QGraphicsScene *scene = new QGraphicsScene();
    InputHandler* view_global = new InputHandler(NULL);

    view_global->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_global->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_global->setFixedSize(screen_initial_width, screen_initial_height);     //1000 : width (X Axis) , 800 : height (Y Axis)
    view_global->setSceneRect(0,0,screen_initial_width, screen_initial_height);

    StartButton* start_button = new StartButton(&a , scene , view_global , "PLAY GAME");
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
