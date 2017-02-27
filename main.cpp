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
#include <startbutton.h>
#include<QGraphicsScene>
#include<QGraphicsProxyWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QRect rec = QApplication::desktop()->availableGeometry();
    int screen_initial_height = rec.height() - 50;
    int screen_initial_width = screen_initial_height * 1.5;

    QGraphicsScene *start_scene = new QGraphicsScene();
    QGraphicsView * initial_view = new QGraphicsView();

    StartButton* start_button = new StartButton(start_scene , initial_view , "PLAY GAME");
    QGraphicsProxyWidget *proxy = start_scene->addWidget(start_button);

    initial_view->setScene(start_scene);
    initial_view->setFixedSize(screen_initial_width,screen_initial_height);
    initial_view->show();
    return a.exec();
}
