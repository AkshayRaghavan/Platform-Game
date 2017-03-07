#include "choiceserverclientstart.h"
#include <QGraphicsTextItem>

ChoiceServerClientStart::ChoiceServerClientStart(QGraphicsScene* scene_local , InputHandler* view_local , int milliseconds_per_frame , int screen_width , int screen_height , Client* game_client /*, Server* game_server */, QWidget *parent)
{
    scene = scene_local;
    view = view_local;
    millisecondsPerFrame = milliseconds_per_frame;
    screenWidth = screen_width;
    screenHeight = screen_height;
    client = game_client;
}

void ChoiceServerClientStart::startClient()
{
    foreach(QGraphicsItem *item, scene->items())
    {
        scene->removeItem(item);
    }
    qDebug() << "inside startClient";
    QFrame *f = new QFrame();
    QHBoxLayout *flayout = new QHBoxLayout(f);
    InputBox* input_url_text = new InputBox(view , f , flayout , "Enter The URL of The Server And Press The Enter Key" , client);
    flayout->addWidget((input_url_text->lineEdit));
    f->move(screenWidth/3 , screenWidth/3);
    f->setFocus();
    f->show();
}

void ChoiceServerClientStart::startServer()
{
    foreach(QGraphicsItem *item, scene->items())
    {
        scene->removeItem(item);
    }
    qDebug() << "inside startServer";
   // server->startServer();
}


void ChoiceServerClientStart::displayStartMenu()
{
    // create the title text
    QGraphicsTextItem* choosing_server_client_text = new QGraphicsTextItem(QString("CHOOSE YOUR IDENTITY"));
    QFont titleFont("comic sans",50);
    choosing_server_client_text->setFont(titleFont);
    choosing_server_client_text->setPos(view->width()/2 - choosing_server_client_text->boundingRect().width()/2,view->height()/5);
    scene->addItem(choosing_server_client_text);

    // create the server button
    Button* server_button = new Button(QString("Start Server"));
    server_button->setPos(view->width()/2 - server_button->boundingRect().width()/2,view->height()/3);
    QObject::connect(server_button,SIGNAL(clicked()),this,SLOT(startServer()));
    scene->addItem(server_button);

    // create the client buttonquit_button
    Button* client_button = new Button(QString("Start Client"));
    client_button->setPos(view->width()/2 - client_button->boundingRect().width()/2,view->height()/(2.5));
    QObject::connect(client_button,SIGNAL(clicked()),this,SLOT(startClient()));
    scene->addItem(client_button);

    // create the client button
    Button* quit_button = new Button(QString("Quit"));
    quit_button->setPos(view->width()/2 - quit_button->boundingRect().width()/2,view->height()/(2.15));
    QObject::connect(quit_button,SIGNAL(clicked()),view,SLOT(close()));
    scene->addItem(quit_button);
}
