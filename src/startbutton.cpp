#include "startbutton.h"

StartButton::StartButton(QApplication* a ,QGraphicsScene* scene_local,InputHandler* view_local,const char* button_text , int milliseconds_per_frame, int screen_width, int screen_height)
{
    millisecondsPerFrame = milliseconds_per_frame;
    core = a;
    scene = scene_local;
    view_global = view_local;
    this->setGeometry(QRect(50,50,120,120));
    this->setText(button_text);
    screenWidth = screen_width;
    screenHeight = screen_height;
    QObject::connect(this,SIGNAL(clicked()),this,SLOT(changeEvent()));
}
void StartButton::setProxy(QGraphicsProxyWidget* x)
{
    proxyVector.push_back(x);
}

void StartButton::changeEvent()
{
    for(auto it = proxyVector.begin() ; it < proxyVector.end() ; it++)
    {
        scene->removeItem(*it);
    }

    ReadInput readInput(scene,screenWidth,screenHeight);
    GameState * gameState = readInput.createGameStateObject("resources/game files/tile map level1/tile map level1.txt" , "resources/game files/gems/diamond map level1.txt" , "resources/game files/player/player1 level1.txt" , "resources/game files/player/player2 level1.txt" , "resources/game files/monster/monster level1.txt" , "resources/game files/fire/fire level1.txt" , "resources/game files/door/door.txt" , millisecondsPerFrame);

    QImage *back = new QImage("resources/images/bg2.png");
    QImage *background = new QImage(back->scaled(gameState->screenWidth, gameState->screenHeight ,Qt::IgnoreAspectRatio,Qt::FastTransformation));
    QBrush *brush = new QBrush(*background);
    view_global->setBackgroundBrush(*brush);

    view_global->setGameState(gameState);
    scene->update();
    view_global->update();
    QTimer * timer = new QTimer();
    gameState->connect(timer,SIGNAL(timeout()),gameState,SLOT(update()));
    timer->start(40);
}
