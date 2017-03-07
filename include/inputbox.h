#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QLineEdit>
#include <QUrl>
#include <QObject>
#include <QHBoxLayout>
#include "inputhandler.h"
#include "client.h"

class InputBox : public QObject
{
    Q_OBJECT
    QGraphicsScene* scene;
    QLabel* label;
    QFrame* f;
    QHBoxLayout* flayout;
    Client * client;
    InputHandler *view;
    QGraphicsTextItem* clientMessage;
public:
    QLineEdit* lineEdit;
    InputBox(InputHandler* , QGraphicsScene* , QLabel* ,QFrame* , QHBoxLayout* , const char* , Client* , QGraphicsTextItem*);
private slots:
    void pingServer();
};
#endif // INPUTBOX_H
