#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QLineEdit>
#include <QUrl>
#include <QObject>
#include <QHBoxLayout>
#include "inputhandler.h"
#include "client.h"
#include "loadingtext.h"

class InputBox : public QObject
{
    Q_OBJECT
    QFrame* f;
    QHBoxLayout* flayout;
    Client * client;
    InputHandler *view;
public:
    QLineEdit* lineEdit;
    InputBox(InputHandler* , QFrame* , QHBoxLayout* , const char* , Client*);
private slots:
    void pingServer();
};
#endif // INPUTBOX_H
