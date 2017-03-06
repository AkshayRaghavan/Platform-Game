#ifndef SERVER_H
#define SERVER_H
#include<QGraphicsScene>
#include<QGraphicsView>
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
#include <QLabel>
#include <QMovie>
#include <QSize>
#include <QApplication>
#include <QGraphicsProxyWidget>

class InputHandler;

class  Client: public QObject
{
    Q_OBJECT
private:
    QWebSocket clientWebSocket;
    const QUrl url;
    const int screenHeight;
    const int screenWidth;
    int noOfPlayers;
    int arrayIndexInGameObject;
    bool receivedNoOfPlayerFlag;
    bool isAcceptingGameState;
    QGraphicsScene *scene;
    InputHandler *view;
    ReadInput* createGamePointer;
    QLabel *label;
    QApplication *app;
    const int millisecondsPerFrame;
    void setGameStartedVal();
    void startGame(std::string , std::string , std::string , std::string , std::string , std::string , std::string , int );

Q_SIGNALS:
    void closed();

signals:
    void textChanged(QString);
    
protected Q_SLOTS:
    void Error(QAbstractSocket::SocketError error);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString);
    void onBinaryMessageReceived(QByteArray);
public:
    GameState* gamePointer;
    Client(QUrl, int , QGraphicsScene* , InputHandler* , int , int , QObject *parent = 0);
    int getArrayIndex();
    QWebSocket* getClientWebSocket();
    void DisplayScore(QJsonArray score);
    void setApp(QApplication *);

};
#endif // SERVER_H
