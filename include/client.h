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
    QString name;
    QApplication* app;
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
    QLabel *label;
    QGraphicsTextItem* clientLoadingMessage;
    const int millisecondsPerFrame;
    void setGameStartedVal();
    void startGame(std::string , std::string , std::string , std::string , std::string , std::string , std::string , std::string , int );

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
    Client(QApplication* , int , QGraphicsScene* , InputHandler* , int , int , QLabel* , QObject *parent = 0);
    ~Client();
    int getArrayIndex();
    QWebSocket* getClientWebSocket();
    void DisplayScore(QString);
    void connectToServer(QUrl , QGraphicsTextItem* , QString);
};
#endif // SERVER_H
