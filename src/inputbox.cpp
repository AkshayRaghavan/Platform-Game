#include "inputbox.h"

InputBox::InputBox(QFrame* f_local , QHBoxLayout* flayout_local , const char* text , Client* client_local)
{
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

  //  flayout->removeWidget(lineEdit);
    client->connectToServer(QUrl("ws://"+lineEdit->text()+":3000"));
    f->close();

}
