#ifndef CHOICESERVERCLIENTSTART_H
#define CHOICESERVERCLIENTSTART_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QDebug>
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "server.h"
#include "client.h"
#include "inputhandler.h"
#include "button.h"
class ChoiceServerClientStart :public QObject
{
    Q_OBJECT
    QLabel* label;
    QFrame* fGlobal;
    QGraphicsTextItem* clientMessage;
    QLineEdit* inputURL;
    QLineEdit* name;

    QGraphicsScene* scene;
    InputHandler* view;
    int millisecondsPerFrame;
    int screenWidth;
    int screenHeight;
    Client* client;
    Server * server;
public:
    ChoiceServerClientStart(QGraphicsScene* , InputHandler* , const char * , int , int , int , Client* , Server* , QLabel* ,QWidget *parent = NULL);
    ~ChoiceServerClientStart();
    void displayStartMenu();
private slots:
    void startClient();
    void startServer();
    void startServerGameSlotButtonClick();
    void startClientGameSlotButtonClick();

};

#endif // CHOICESERVERCLIENTSTART_H
