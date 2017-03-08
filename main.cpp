#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include <QEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QStyle>
#include <QMediaPlayer>
#include <QFileInfo>
#include <QDesktopWidget>
#include "server.h"
#include "readinput.h"
#include "server.h"
#include "client.h"
#include "gamestate.h"
#include "gameobject.h"
#include "inputhandler.h"
#include "choiceserverclientstart.h"
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    int milliseconds_per_frame = 50;
    QApplication a(argc, argv);
    QGraphicsScene *scene = new QGraphicsScene;
    InputHandler *view = new InputHandler(NULL);

    QRect rec = QApplication::desktop()->availableGeometry();
    int screen_height = rec.height() - 2*view->frameWidth() - QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    int screen_width = screen_height * 1.5;

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(screen_width, screen_height);
    view->setSceneRect(0,0,screen_width, screen_height);
    view->setScene(scene);
    view->show();

    QLabel *label = new QLabel;
    QMovie *mov = new QMovie("resources/images/loading.gif");
    mov->start();
    label->setAttribute(Qt::WA_NoSystemBackground);
    label->setMovie(mov);
    mov->setScaledSize(QSize(screen_width/20,screen_height/20));
    label->move(100*(screen_width/240),85*(screen_height/160));
    
    Server game_server(3000 , &a , scene ,  milliseconds_per_frame , 4 , label);
    Client game_client(&a , milliseconds_per_frame , scene , view , screen_width , screen_height , label);
    ChoiceServerClientStart* startButton = new ChoiceServerClientStart(scene , view , "resources/images/assets/server client start button/background.png" , milliseconds_per_frame , screen_width , screen_height ,  &game_client , &game_server , label);
    startButton->displayStartMenu();
    return a.exec();
}
