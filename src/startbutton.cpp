#include "startbutton.h"

StartButton::StartButton(QGraphicsScene* scene_local,QGraphicsView* view_local,const char* button_text)
{
    scene = scene_local;
    view_global = view_local;
    this->setGeometry(QRect(50,50,120,120));
    this->setText(button_text);
    QObject::connect(this,SIGNAL(clicked()),this,SLOT(changeEvent()));
}
void StartButton::changeEvent()
{
     scene->clear();
     delete scene;
    QGraphicsScene *new_scene = new QGraphicsScene();

    ReadInput readInput(new_scene);
    GameState * gameState = readInput.createGameStateObject("resources/game files/tile map level1/tile map level1.txt" , "resources/game files/gems/diamond map level1.txt" , "resources/game files/player/player1 level1.txt" , "resources/game files/player/player2 level1.txt" , "resources/game files/monster/monster level1.txt" , "resources/game files/fire/fire level1.txt" , "resources/game files/door/door.txt");

    InputHandler* view = new InputHandler(gameState);
   // view_global = static_cast<InputHandler*> (new InputHandler(gameState));

    QImage *back = new QImage("resources/images/bg2.png");
    QImage *background = new QImage(back->scaled(gameState->screenWidth, gameState->screenHeight ,Qt::IgnoreAspectRatio,Qt::FastTransformation));
    QBrush *brush = new QBrush(*background);
    view->setBackgroundBrush(*brush);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(gameState->screenWidth, gameState->screenHeight);     //1000 : width (X Axis) , 800 : height (Y Axis)
    view->setSceneRect(0,0,gameState->screenWidth, gameState->screenHeight);
    view->setScene(new_scene);

    view_global = view;
    view_global->update();
   // scene->removeItem(this);
   // view_global->update();
    //view->show();


    QTimer * timer = new QTimer();
    gameState->connect(timer,SIGNAL(timeout()),gameState,SLOT(update()));
    timer->start(40);
}
