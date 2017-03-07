#ifndef SERVER_H
#define SERVER_H
#include <QWebSocketServer>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <iterator>
#include <QCoreApplication>
#include "gamestate.h"
#include "readinput.h"
class  Server: public QObject
{
    Q_OBJECT
private:
    std::vector<std::thread> client_threads;
    QWebSocketServer* webSocketServer;
    QList<QWebSocket *> webSocketClients;
    bool maxConnectionsReached;
    bool gameStarted;
    int gameStartedCountOfClients;
    QGraphicsScene* scene;
    ReadInput* createGamePointer;
    const int millisecondsPerFrame;
    QJsonObject convertGameStateToJsonObject(GameState &);
    std::string getStringFromGameState(GameState &);
    void startServerGameLoop();
    void sendIndexToCLient();
    void setGameStartedVal();
    void startGame(std::string , std::string , std::string , std::string ,
                   std::string , std::string  , int );

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString);
    void processBinaryMessage(QByteArray);
    void socketDisconnected();
    void iterateOverGameState();

public:
    GameState* gamePointer;
    Server(quint16 , QGraphicsScene* , int , int , int , QObject *parent = 0);
    ~Server();

};
#endif // SERVER_H
