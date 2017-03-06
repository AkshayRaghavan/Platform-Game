#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include <QEvent>
#include <QDebug>
#include "client.h"
#include "readinput.h"
#include "gamestate.h"
#include "gameobject.h"
#include "inputhandler.h"

#include "loadingtext.h"

#include <QDesktopWidget>
#include "inputbox.h"
#include "exitbutton.h"
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QStyle>
#include <QMediaPlayer>
#include <QFileInfo>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{

    int milliseconds_per_frame = 50;
    QApplication a(argc, argv);

    //   gameState->installEventFilter(view); //set focus?
    //   QGraphicsView *view = new QGraphicsView;
    //   QMediaPlayer * bg = new QMediaPlayer();
    //  QFileInfo file("resources/game files/bg.mp3");
    //  bg->setMedia(QUrl("file://resources/game files/bg.mp3"));
    //  bg->setMedia(QUrl("file://"+file.absoluteFilePath()));
    //  bg->play();


    QGraphicsScene *scene = new QGraphicsScene;
    InputHandler *view = new InputHandler(NULL);

    QRect rec = QApplication::desktop()->availableGeometry();
    int screen_initial_height = rec.height() - 2*view->frameWidth() - QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    int screen_initial_width = screen_initial_height * 1.5;
    
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(screen_initial_width, screen_initial_height);     //1000 : width (X Axis) , 800 : height (Y Axis)
    view->setSceneRect(0,0,screen_initial_width, screen_initial_height);
    view->setScene(scene);
    view->show();

    QFrame *f = new QFrame();
    InputBox* input_url_text = new InputBox(f ,  scene , view , "Enter The URL of The Server And Press Enter" , milliseconds_per_frame , screen_initial_width, screen_initial_height);
    QHBoxLayout *flayout = new QHBoxLayout(f);
    flayout->addWidget((input_url_text->lineEdit));
    f->move(screen_initial_width/2 , screen_initial_height/2);
    f->setFocus();
    //f->show();


    Client game_client(QUrl(QStringLiteral("ws://localhost:3000")) , milliseconds_per_frame , scene , view , screen_initial_width , screen_initial_height);
    //qDebug () << "Setting application";
    game_client.setApp(&a);
    LoadingText* loading_text = new LoadingText(&game_client , scene , view , 100*(screen_initial_width/240), 60*(screen_initial_height/160));


    return a.exec();
}
