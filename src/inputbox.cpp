#include "inputbox.h"

InputBox::InputBox(InputHandler *view_local  , QFrame* f_local , QHBoxLayout* flayout_local , const char* text , Client* client_local)
{
    view = view_local;
    f = f_local;
    flayout = flayout_local;
    lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText(text);
    lineEdit->setFixedWidth(500);
    lineEdit->setFocus();
    client = client_local;
    QObject::connect(lineEdit,SIGNAL(returnPressed()),this,SLOT(pingServer()));
}

void InputBox::pingServer()
{
    client->connectToServer(QUrl("ws://"+lineEdit->text()+":3000"));
    f->close();
    view->setGameClient(client);
  //  LoadingText* loading_text = new LoadingText(&game_client , scene , view , screenWidth/(3.0) , screenHeight/(3.0));
}
