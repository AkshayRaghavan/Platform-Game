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
    const quint16 port;
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
    Server(quint16 , QGraphicsScene* , int ,  QObject *parent = 0);
    void startServer(int , int);
    void startGameSlotButtonClick();
    ~Server();
};
#endif // SERVER_H
