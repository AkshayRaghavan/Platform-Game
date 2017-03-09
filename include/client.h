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

/*!
 * \brief The Class to Create a Client
 */

class  Client: public QObject
{
    Q_OBJECT
private:
    /*!
     * \brief Name of the Client
     */
    QString name;
    /*!
     * \brief To store the QApplication
     */
    QApplication* app;
    /*!
     * \brief Client Web Socket
     */
    QWebSocket clientWebSocket;
    /*!
     * \brief URL of the Server
     */
    QUrl url;
    /*!
     * \brief Screen Height
     */
    const int screenHeight;
    /*!
     * \brief Screen Width
     */
    const int screenWidth;
    /*!
     * \brief Number of Players on the Server
     */
    int noOfPlayers;
    /*!
     * \brief ID of the Client
     */
    int arrayIndexInGameObject;
    /*!
     * \brief Boolean to check player numebr
     */
    bool receivedNoOfPlayerFlag;
    /*!
     * \brief Boolean to store if it is accepting Game State
     */
    bool isAcceptingGameState;
    /*!
     * \brief The QGraphicsScene to add Items
     */
    QGraphicsScene *scene;
    /*!
     * \brief The View Widget to show Client
     */
    InputHandler *view;
    /*!
     * \brief Reading input from files
     */
    ReadInput* createGamePointer;
    /*!
     * \brief The QLabel
     */
    QLabel *label;
    /*!
     * \brief Message when Client is Loading
     */
    QGraphicsTextItem* clientLoadingMessage;
    /*!
     * \brief Mili Seconds per frame
     */
    const int millisecondsPerFrame;
    /*!
     * \brief Set the value of Game to be started
     */
    void setGameStartedVal();
    /*!
     * \brief Function to start game
     * \param tile_map_path Tile Map Path
     * \param monster_file_path Monster File Path
     * \param fire_file_path Fire File Path
     * \param gem_path Gem File Path
     * \param player_file_path Player File Path
     * \param player_special_path Player Special Path
     * \param door_file_path Door File Path
     * \param bg_image_path Background Image Path
     * \param total_time Total Time
     */
    void startGame(std::string tile_map_path , std::string monster_file_path ,
                   std::string fire_file_path , std::string gem_path ,
                   std::string player_file_path , std::string player_special_path ,
                   std::string door_file_path , std::string bg_image_path ,
                   int total_time);

Q_SIGNALS:
    /*!
     * \brief Signal to be sent when Client closes
     */
    void closed();

signals:
    /*!
     * \brief Text Change Function
     */
    void textChanged(QString);

private Q_SLOTS:
    /*!
     * \brief Tasks to do When connected to server
     */
    void onConnected();
    /*!
     * \brief On Text Message Received
     */
    void onTextMessageReceived(QString);
    /*!
     * \brief On Binary Message Received
     */
    void onBinaryMessageReceived(QByteArray);
public:
    /*!
     * \brief The GameState Pointer
     */
    GameState* gamePointer;
    /*!
     * \brief Client Constructor
     * \param parent
     */
    Client(QApplication* , int , QGraphicsScene* , InputHandler* , int , int , QLabel* , QObject *parent = 0);
    /*!
     * \brief Client Destructor
     */
    ~Client();
    /*!
     * \brief Get the Player ID
     * \return Player ID
     */
    int getArrayIndex();
    /*!
     * \brief The Client Websocket
     * \return clientwebsocket
     */
    QWebSocket* getClientWebSocket();
    /*!
     * \brief Display The Score
     */
    void DisplayScore(QString);
    /*!
     * \brief Connect To Server
     */
    void connectToServer(QUrl , QGraphicsTextItem* , QString);
};
#endif // SERVER_H
