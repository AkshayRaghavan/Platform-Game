#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include <QEvent>
#include <QDebug>
#include "client.h"
#include "server.h"

#include "readinput.h"
#include "gamestate.h"
#include "gameobject.h"
#include "inputhandler.h"

#include "loadingtext.h"
#include "choiceserverclientstart.h"

#include <QDesktopWidget>
#include "inputbox.h"
#include "exitbutton.h"
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QStyle>
#include <QMediaPlayer>
#include <QFileInfo>

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
    
  //  Server* game_server = new Server(3000 , scene , screen_width , screen_height , milliseconds_per_frame);
    Client* game_client = new Client(milliseconds_per_frame , scene , view , screen_width , screen_height);
    ChoiceServerClientStart* startButton = new ChoiceServerClientStart(scene , view , milliseconds_per_frame , screen_width , screen_height , game_client/* , game_server*/);
    startButton->displayStartMenu();

  /*  InitialChoiceServerButton* initial_choice_server_button = new InitialChoiceServerButton(scene , view , "START SERVER" , milliseconds_per_frame, screen_width, screen_height);
    QGraphicsProxyWidget * start_proxy = scene->addWidget(initial_choice_server_button);
    start_proxy->setPos(500 , 500);
*/
 /*   Client game_client(milliseconds_per_frame , scene , view , screen_width , screen_height);

    QFrame *f = new QFrame();
    QHBoxLayout *flayout = new QHBoxLayout(f);
    InputBox* input_url_text = new InputBox(view  , f , flayout , "Enter The URL of The Server And Press Enter" , &game_client);

    flayout->addWidget((input_url_text->lineEdit));
    f->move(screen_width/2 , screen_height/2);
    f->setFocus();
    f->show();*/

    //LoadingText* loading_text = new LoadingText(&game_client , scene , view , screen_width/(3.0) , screen_height/(3.0));
    //connect(&game_client);
    return a.exec();
}
