#ifndef CLIENT_H
#define CLIENT_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QJsonArray>
#include <iterator>
#include <QCoreApplication>
#include <QtCore/QDebug>
#include <QJsonObject>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <thread>
#include "QtWebSockets/qwebsocket.h"
#include "inputhandler.h"
#include "gamestate.h"
#include "gameobject.h"
#include "readinput.h"
#include "movingleft.h"
#include "movingright.h"
#include "deadleft.h"
#include "deadright.h"
#include "enumerator.h"
#include "isjumping.h"
#include "isnotjumping.h"

class InputHandler;

class  Client: public QObject
{
    Q_OBJECT
private:
    QWebSocket clientWebSocket;
    QUrl url;
    const int screenHeight;
    const int screenWidth;
    int noOfPlayers;
    int arrayIndexInGameObject;
    bool receivedNoOfPlayerFlag;
    bool isAcceptingGameState;
    QGraphicsScene *scene;
    InputHandler *view;
    ReadInput* createGamePointer;
    const int millisecondsPerFrame;
    void setGameStartedVal();
    void startGame(std::string , std::string , std::string , std::string , std::string , std::string , std::string , int );

Q_SIGNALS:
    void closed();

signals:
    void textChanged(QString);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString);
    void onBinaryMessageReceived(QByteArray);
public:
    GameState* gamePointer;
    Client(int , QGraphicsScene* , InputHandler* , int , int , QObject *parent = 0);
    int getArrayIndex();
    QWebSocket* getClientWebSocket();
    void DisplayScore(QJsonArray score);
    void connectToServer(QUrl);

};
#endif // SERVER_H
