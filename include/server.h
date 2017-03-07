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
#include "threadpool.h"

class  Server: public QObject
{
    Q_OBJECT
private:
    QApplication * app;
    const quint16 port;
    std::vector<std::thread> client_threads;
    QWebSocketServer* webSocketServer;
    QList<QWebSocket *> webSocketClients;
    bool maxConnectionsReached;
    bool gameStarted;
    int gameStartedCountOfClients;
    ThreadPool threadPool;
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
    QGraphicsTextItem* clientIPList;

Q_SIGNALS:
    void closed();
    void contentsChanged(QString);

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString);
    void processBinaryMessage(QByteArray);
    void socketDisconnected();
    void iterateOverGameState();

public:
    GameState* gamePointer;
    Server(quint16 , QApplication* , QGraphicsScene* , int , int , QObject *parent = 0);
    void startServer(int , int);
    void startGameSlotButtonClick();
    void setClientIPList(QGraphicsTextItem* client_IP_list);
    ~Server();
};
#endif // SERVER_H
