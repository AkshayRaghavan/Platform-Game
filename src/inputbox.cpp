#include "inputbox.h"

InputBox::InputBox(QFrame* f_local , QGraphicsScene* scene_local,InputHandler* view_local,const char* text ,
                   int milliseconds_per_frame, int screen_width, int screen_height)
{
    f = f_local;
    lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText(text);
    millisecondsPerFrame = milliseconds_per_frame;
    scene = scene_local;
    view = view_local;
    lineEdit->setFixedWidth(500);
    lineEdit->setFocus();
    //this->releaseKeyboard();
    screenWidth = screen_width;
    screenHeight = screen_height;
   // Client game_client(QUrl(QStringLiteral("ws://localhost:3000")) , millisecondsPerFrame , scene , view , screenWidth , screenHeight , new QGraphicsTextItem);

  //  QObject::connect(lineEdit,SIGNAL(returnPressed()),this,SLOT(pingServer()));
}

void InputBox::pingServer()
{
    qDebug() << "In slot";
    messageToClient = new QGraphicsTextItem;
    messageToClient->setPos(screenWidth/3 , screenHeight/3);
    messageToClient->setPlainText("Contacting Server .....");
    scene->addItem(messageToClient);
    qDebug() << "TEXT : " << lineEdit->text();
        QString a = lineEdit->text();
        qDebug() << "************ : "<<a;
     //   delete f;
        Client game_client(QUrl(QStringLiteral("ws://localhost:3000")) , millisecondsPerFrame , scene , view , screenWidth , screenHeight , new QGraphicsTextItem);
}
