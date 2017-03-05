#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QLineEdit>
#include <QGraphicsTextItem>
#include<QGraphicsProxyWidget>
#include <QUrl>
#include <QObject>
#include "inputhandler.h"
#include "client.h"
class InputBox : public QObject
{
    Q_OBJECT
    int millisecondsPerFrame;
    QGraphicsScene* scene;
    InputHandler* view;
    int screenWidth;
    int screenHeight;
    QFrame* f;
 public:
    QLineEdit* lineEdit;
    QGraphicsTextItem* messageToClient;
    InputBox(QFrame* , QGraphicsScene* , InputHandler* , const char* , int, int, int );
public slots:
    void pingServer();
};
#endif // INPUTBOX_H
