#include "choiceserverclientstart.h"
#include <QGraphicsTextItem>

ChoiceServerClientStart::ChoiceServerClientStart(QGraphicsScene* scene_local , InputHandler* view_local , const char * bg_image_path , int milliseconds_per_frame , int screen_width , int screen_height , Client* game_client , Server* game_server , QLabel* label_formal ,QWidget *parent)
{
    label =label_formal;
    scene = scene_local;
    view = view_local;
    millisecondsPerFrame = milliseconds_per_frame;
    screenWidth = screen_width;
    screenHeight = screen_height;
    client = game_client;
    server = game_server;
    QImage *back = new QImage(bg_image_path);
    if(back->isNull())
    {
        qDebug() << "ERROR(choiceserverclientstart.cpp) : Failed To Load Image" << bg_image_path;
        std::exit(EXIT_FAILURE);
    }
    QImage *background = new QImage(back->scaled(screenWidth,screenHeight ,Qt::IgnoreAspectRatio,Qt::FastTransformation));
    QBrush *brush = new QBrush(*background);
    view->setBackgroundBrush(*brush);
}

void ChoiceServerClientStart::startClient()
{
    foreach(QGraphicsItem *item, scene->items())
    {
        scene->removeItem(item);
    }
    QGraphicsTextItem* client_message = new QGraphicsTextItem(QString(""));
    client_message->setFont(QFont("ocr a extended",screenHeight/30));
    client_message->setPos(view->width()/(4) - client_message->boundingRect().width()/2,view->height()/3);
    scene->addItem(client_message);
    clientMessage = client_message;

    qDebug() << "inside startClient";
    QFrame *f = new QFrame();
    fGlobal = f;
    QHBoxLayout *flayout = new QHBoxLayout(f);

    QLineEdit* input_url_text = new QLineEdit(f);
    input_url_text->setPlaceholderText("Enter The URL of The Server And Press The Enter Key");
    input_url_text->setFixedWidth(200);
    input_url_text->setFocus();
    inputURL = input_url_text;

    QLineEdit* name_text = new QLineEdit(f);
    name_text->setPlaceholderText("Enter Your Username");
    name_text->setFixedWidth(200);
    name = name_text;

    QPushButton* button = new QPushButton("START", f);
    QObject::connect(button , SIGNAL(clicked()) , this , SLOT(startClientGameSlotButtonClick()));
    flayout->addWidget(input_url_text);
    flayout->addWidget(name_text);
    flayout->addWidget(button);

    f->move(screenWidth/3 , screenHeight/3);
    f->setFocus();
    f->show();
}

void ChoiceServerClientStart::startClientGameSlotButtonClick()
{
    scene->addWidget(label);
    clientMessage->setHtml("Connecting To Server....");
    client->connectToServer(QUrl("ws://"+inputURL->text()+":3000") , clientMessage , name->text());
    fGlobal->close();
    view->setGameClient(client);
}
void ChoiceServerClientStart::startServer()
{
    foreach(QGraphicsItem *item, scene->items())
    {
        scene->removeItem(item);
    }
    qDebug() << "inside startServer";
    server->startServer(screenWidth , screenHeight);
    qDebug() << "Outside server";

    QGraphicsTextItem* heading = new QGraphicsTextItem(QString("Number Of Connected Players"));
    heading->setFont(QFont("ocr a extended",35));
    heading->setPos(view->width()/2 - heading->boundingRect().width()/2,view->height()/6);
    scene->addItem(heading);

    QGraphicsTextItem* client_IP_list = new QGraphicsTextItem(QString(""));
    server->setClientIPList(client_IP_list);
    client_IP_list->setFont(QFont("comic sans",15));
    client_IP_list->setPos(view->width()/(2.5) - client_IP_list->boundingRect().width()/2,view->height()/(5.2));
    scene->addItem(client_IP_list);

    // create the start game button
    Button* server_button = new Button("resources/images/assets/server client start button/start1.png" , "resources/images/assets/server client start button/start2.png" , screenWidth , screenHeight);
    server_button->setPos(view->width()/2 - server_button->boundingRect().width()/2,view->height()/2);
    QObject::connect(server_button,SIGNAL(clicked()),this,SLOT(startServerGameSlotButtonClick()));
    scene->addItem(server_button);
}

void ChoiceServerClientStart::startServerGameSlotButtonClick()
{
    foreach(QGraphicsItem *item, scene->items())
    {
        scene->removeItem(item);
    }
    scene->addWidget(label);
    QGraphicsTextItem* server_message = new QGraphicsTextItem(QString(""));
    server_message->setFont(QFont("comic sans",25));
    server_message->setPos(view->width()/(6.5) - server_message->boundingRect().width()/2,view->height()/3);
    scene->addItem(server_message);
    server->startGameSlotButtonClick(server_message);
    QImage *back = new QImage("resources/images/assets/server client start button/background_score.png");
    if(back->isNull())
    {
        qDebug() << "ERROR(choiceserverclientstart.cpp) : Failed To Load Image resources/images/assets/server client start button/background_score.png";
        std::exit(EXIT_FAILURE);
    }
    QImage *background = new QImage(back->scaled(screenWidth,screenHeight ,Qt::IgnoreAspectRatio,Qt::FastTransformation));
    QBrush *brush = new QBrush(*background);
    view->setBackgroundBrush(*brush);
}


void ChoiceServerClientStart::displayStartMenu()
{
    // create the title text
    QGraphicsTextItem* choosing_server_client_text = new QGraphicsTextItem(QString("PLATFORM GAME"));
    choosing_server_client_text->setFont(QFont("algerian",50));
    choosing_server_client_text->setDefaultTextColor(QColor(128,0,128));
    choosing_server_client_text->setPos(view->width()/2 - choosing_server_client_text->boundingRect().width()/2,view->height()/6);
    scene->addItem(choosing_server_client_text);

    // create the server button
    Button* server_button = new Button("resources/images/assets/server client start button/start1.png" , "resources/images/assets/server client start button/start2.png" , screenWidth , screenHeight);
    server_button->setPos(view->width()/2 - server_button->boundingRect().width()/2,view->height()/3);
    QObject::connect(server_button,SIGNAL(clicked()),this,SLOT(startServer()));
    scene->addItem(server_button);

    // create the client buttonquit_button
    Button* client_button = new Button("resources/images/assets/server client start button/join1.png" , "resources/images/assets/server client start button/join2.png" , screenWidth , screenHeight);
    client_button->setPos(view->width()/2 - client_button->boundingRect().width()/2,view->height()/(2.5));
    QObject::connect(client_button,SIGNAL(clicked()),this,SLOT(startClient()));
    scene->addItem(client_button);

    // create the client button
    Button* quit_button = new Button("resources/images/assets/server client start button/quit1.png" , "resources/images/assets/server client start button/quit2.png" , screenWidth , screenHeight);
    quit_button->setPos(view->width()/2 - quit_button->boundingRect().width()/2,view->height()/(2.15));
    QObject::connect(quit_button,SIGNAL(clicked()),view,SLOT(close()));
    scene->addItem(quit_button);
}
