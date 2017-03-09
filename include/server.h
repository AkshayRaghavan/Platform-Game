#ifndef SERVER_H
#define SERVER_H
#include <QWebSocketServer>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <iterator>
#include <QCoreApplication>
#include <QLabel>
#include "gamestate.h"
#include "readinput.h"
#include "threadpool.h"

/*!
 * \brief for making networking websocket server
 */
class  Server: public QObject
{
    Q_OBJECT
private:
    /*!
     * \brief QApplication
     */
    QApplication * app;

    /*!
     * \brief const server port
     */
    const quint16 port;

    /*!
     * \brief the webSocketServer
     */
    QWebSocketServer* webSocketServer;

    /*!
     * \brief vector of clients
     */
    QList<QWebSocket *> webSocketClients;

    /*!
     * \brief bool for server start game click
     */
    bool maxConnectionsReached;

    /*!
     * \brief telling game has started
     */
    bool gameStarted;

    /*!
     * \brief stop or resume server game loop
     */
    bool serverLoopRunning; 

    /*!
     * \brief count of responses
     */
    int gameStartedCountOfClients;

    /*!
     * \brief threadpool for client incoming messages
     */
    ThreadPool threadPool;

    /*!
     * \brief Qscene
     */
    QGraphicsScene* scene;

    /*!
     * \brief the readInput pointer
     */
    ReadInput* createGamePointer;

    /*!
     * \brief milliseconds for timer
     */
    const int millisecondsPerFrame;

    /*!
     * \brief convert gamestate obj to json
     * \param obj the gamestate object
     * \return  a json for sending to client
     */
    QJsonObject convertGameStateToJsonObject(GameState &obj);

    /*!
     * \brief convert gamestate string to json
     * \param obj the gamestate object
     * \return  a string of gamestate
     */
    std::string getStringFromGameState(GameState &obj);

    /*!
     * \brief get leaderboard in HTML
     */
    void getLeaderBoard();

    /*!
     * \brief function called on button click
     */
    void startServerGameLoop();

    /*!
     * \brief send the player number to client
     */
    void sendIndexToCLient();

    /*!
     * \brief render the server game screen
     */
    void setGameStartedVal();

    /*!
     * \brief send the text files
     */
    void startGame(std::string , std::string , std::string , std::string ,
                   std::string , std::string  , int );

    /*!
     * \brief display no of clients
     */
    QGraphicsTextItem* clientIPList;

    /*!
     * \brief server loading message
     */
    QGraphicsTextItem* serverLoadingMessage;

    /*!
     * \brief Qlabel for server start button
     */
    QLabel* label;

Q_SIGNALS:
    /*!
     * \brief signal to close screen
     */
    void closed();

    /*!
     * \brief signal for changing content on screen
     */
    void contentsChanged(QString);

private Q_SLOTS:
    /*!
     * \brief slot when new client connects
     */
    void onNewConnection();

    /*!
     * \brief text
     * \param clients text message
     */
    void processTextMessage(QString message);


    /*!
     * \brief binary
     * \param clients binary message
     */
    void processBinaryMessage(QByteArray);
    
    
    /*!
     * \brief client disconnect
     */
    void socketDisconnected();
    
    
    /*!
     * \brief server loop
     */
    void iterateOverGameState();

public:
    
    /*!
     * \brief gamestate pointer
     */
    GameState* gamePointer;

    /*!
     * \brief constructor
     */
    Server(quint16 port, QApplication * a , QGraphicsScene* scene_local , int milliseconds_per_frame , int number_of_threads , QLabel* label , QObject *parent = NULL);

    /*!
     * \brief destructor
     */
    ~Server();

    /*!
     * \brief button click
     * \param screen width
     * \param screen height
     */
    void startServer(int screen_width , int screen_height);

    /*!
     * \brief display no of connection
     * \param client_IP_list textItem pointer
     */
    void setClientIPList(QGraphicsTextItem* client_IP_list);
    /*!
     * \brief button click
     */
    void startGameSlotButtonClick(QGraphicsTextItem* server_message);

};
#endif // SERVER_H
