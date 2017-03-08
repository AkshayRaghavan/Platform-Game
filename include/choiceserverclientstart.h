#ifndef CHOICESERVERCLIENTSTART_H
#define CHOICESERVERCLIENTSTART_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QDebug>
#include <QFrame>
#include <QHBoxLayout>
#include "server.h"
#include "inputbox.h"
#include "client.h"
#include "inputhandler.h"
#include "button.h"
class ChoiceServerClientStart :public QObject
{
    Q_OBJECT
    QLabel* label;
    QGraphicsScene* scene;
    InputHandler* view;
    int millisecondsPerFrame;
    int screenWidth;
    int screenHeight;
    Client* client;
    Server * server;
public:
    ChoiceServerClientStart(QGraphicsScene* , InputHandler* , const char * , int , int , int , Client* , Server* , QLabel* ,QWidget *parent = NULL);
    void displayStartMenu();
private slots:
    void startClient();
    void startServer();
    void startGameSlotButtonClick();
};

#endif // CHOICESERVERCLIENTSTART_H
