#ifndef CHOICESERVERCLIENTSTART_H
#define CHOICESERVERCLIENTSTART_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QDebug>
#include <QFrame>
#include <QHBoxLayout>
//#include "server.h"
#include "inputbox.h"
#include "client.h"
#include "inputhandler.h"
#include "loadingtext.h"
#include "button.h"
class ChoiceServerClientStart :public QObject
{
    Q_OBJECT
    QGraphicsScene* scene;
    InputHandler* view;
    int millisecondsPerFrame;
    int screenWidth;
    int screenHeight;
    Client* client;
   // Server * server;
public:
    ChoiceServerClientStart(QGraphicsScene* , InputHandler* , int , int , int , Client* ,/* Server * server = NULL , */QWidget *parent = NULL);
    void displayStartMenu();

private slots:
    void startClient();
    void startServer();};

#endif // CHOICESERVERCLIENTSTART_H
