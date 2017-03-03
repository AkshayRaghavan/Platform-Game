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
    QWebSocketServer* webSocketServer;
    const bool websocketDebug;
    QList<QWebSocket *> webSocketClients;
    bool gameStarted;

    ReadInput* createGamePointer;
    const int millisecondsPerFrame;
    QJsonObject convertGameStateToJsonObject(GameState &);
    std::string getStringFromGameState(GameState &);
    void startServerGameLoop();
    void sendIndexToCLient();
    void iterateOverGameState();
    void setGameStartedVal();
    void startGame(std::string , std::string , std::string , std::string , std::string , std::string , int , int );

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
public:
    GameState* gamePointer;
    Server(quint16, bool , QGraphicsScene* , int , int , int , QObject *parent = 0);
    ~Server();




};
#endif // SERVER_H
