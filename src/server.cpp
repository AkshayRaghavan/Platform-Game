#include "server.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <QJsonObject>
#include <QTimer>
#include <QKeyEvent>
QT_USE_NAMESPACE

Server::Server(quint16 port, bool debug, QGraphicsScene* scene , int screen_width ,
               int screen_height ,  int milliseconds_per_frame , QObject *parent) :
    QObject(parent),
    webSocketServer(new QWebSocketServer(QStringLiteral("Platform Game Server"),
                                         QWebSocketServer::NonSecureMode, this)),
    websocketDebug(debug),
    millisecondsPerFrame(milliseconds_per_frame)
{
    createGamePointer = new ReadInput(scene,screen_width,screen_height);
    gameStarted = false;
    if (webSocketServer->listen(QHostAddress::Any, port)) {
        if (websocketDebug)
            qDebug() << "Server listening on port" << port;
        connect(webSocketServer, &QWebSocketServer::newConnection,
                this, &Server::onNewConnection);
        connect(webSocketServer, &QWebSocketServer::closed, this, &Server::closed);
    }
    else
    {
        qDebug() << "Error In Connecting To Port : " << port;
        qDebug() << "Error Message : " << webSocketServer->errorString();
        std::exit(EXIT_FAILURE);
    }
}

Server::~Server()
{
    webSocketServer->close();
    qDeleteAll(webSocketClients.begin(), webSocketClients.end());
}

void Server::onNewConnection()
{
    qDebug() << "Got A New Connection For Game";
    QWebSocket *pSocket = webSocketServer->nextPendingConnection();
    if(gameStarted)
    {
        pSocket->sendTextMessage("Game Has Started . Please Join Us For The Next Game.");
    }
    else
    {
        QObject::connect(pSocket, &QWebSocket::binaryMessageReceived, this, &Server::processBinaryMessage);
        QObject::connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);
        webSocketClients << pSocket;
        pSocket->sendTextMessage("successfully connected. Waiting For Game To Start");
        qDebug() << "Added To webSocketClients And Sent Response Message";
        if(webSocketClients.size() == 2)
            setGameStartedVal();
    }
}

void Server::setGameStartedVal()
{
    gameStarted = true;
    startGame( "resources/game files/tile map level1/tile map level1.txt" ,
               "resources/game files/monster/monster level1.txt" ,
               "resources/game files/fire/fire level1.txt" ,
               "resources/game files/gems/diamond map level1.txt" ,
               "resources/game files/player/player level1.txt" ,
               "resources/game files/door/door.txt" ,
               millisecondsPerFrame , 60000);

}

void Server::startGame(std::string tile_map_path , std::string monster_file_path ,
                       std::string fire_file_path , std::string gem_path ,
                       std::string player_file_path , std::string door_file_path ,
                       int milliseconds_per_frame , int total_time)
{
    createGamePointer->functionToCreateTileMap(tile_map_path);
    createGamePointer->functionToCreateMonsterGameObject(monster_file_path);
    createGamePointer->functionToCreateFireObject(fire_file_path);
    createGamePointer->functionToCreateGem(gem_path);
    createGamePointer->functionToCreateDoor(door_file_path);

    for (int i = 0; i != webSocketClients.size(); i++)
    {
        createGamePointer->functionToCreatePlayerGameObject(player_file_path , Qt::Key_Up, Qt::Key_Right ,  Qt::Key_Left);
    }
    gamePointer = new GameState(createGamePointer->gameObject , createGamePointer->tileMap , createGamePointer->gems , createGamePointer->screenWidth , createGamePointer->screenHeight , createGamePointer->scene , milliseconds_per_frame, total_time);

    QTimer * timer = new QTimer();
    gamePointer->connect(timer,SIGNAL(timeout()), gamePointer ,SLOT(update()));
    timer->start(40);

    sendIndexToCLient();
}


void Server::sendIndexToCLient()
{
    int loop_count_client = 0;
    for (int i = 0; i != (gamePointer->gameObjects).size(); i++)
    {
        if(((((gamePointer->gameObjects)[i])->graphicsComponent)->getIsDangerous()) == false)
        {
            webSocketClients[loop_count_client++]->sendTextMessage(QString::fromStdString(std::to_string(i)));
        }
    }
    startServerGameLoop();
}

void Server::startServerGameLoop()
{
    QTimer * timer = new QTimer();
    gamePointer->connect(timer,SIGNAL(timeout()),gamePointer,SLOT(iterateOverGameState()));
    timer->start(40);
}

void Server::iterateOverGameState()
{
    QJsonObject object = convertGameStateToJsonObject(*gamePointer);
    QJsonDocument doc(object);
    QByteArray bytes = doc.toJson();

    for (QList<QWebSocket*>::iterator i = webSocketClients.begin(); i != webSocketClients.end(); i++)
    {
        (*i)->sendBinaryMessage(bytes);
    }
}

void Server::processBinaryMessage(QByteArray message)
{
    if (websocketDebug)
        qDebug() << "Binary Message received:";
    QJsonDocument item_doc = QJsonDocument::fromJson(message);
    QJsonObject item_object = item_doc.object();
    int array_index = item_object["arrayIndex"].toInt();
    QString eventName = item_object["eventName"].toString();
    QString key = item_object["key"].toString();
    QKeyEvent *event = NULL;

    if(eventName == "keypress")
    {
        if(key == "UP")
        {
            event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Up , Qt::NoModifier);
        }
        else if(key == "LEFT")
        {
            event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Left , Qt::NoModifier);
        }
        else if(key == "RIGHT")
        {
            event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Right , Qt::NoModifier);
        }
    }
    else if(eventName == "keyrelease")
    {
        if(key == "UP")
        {
            event = new QKeyEvent ( QEvent::KeyRelease, Qt::Key_Up , Qt::NoModifier);
        }
        else if(key == "LEFT")
        {
            event = new QKeyEvent ( QEvent::KeyRelease, Qt::Key_Left , Qt::NoModifier);
        }
        else if(key == "RIGHT")
        {
            event = new QKeyEvent ( QEvent::KeyRelease, Qt::Key_Right , Qt::NoModifier);
        }
    }
    QCoreApplication::sendEvent(gamePointer->gameObjects[array_index] , event);
}

void Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (websocketDebug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        webSocketClients.removeAll(pClient);
        pClient->deleteLater();
    }
}


QJsonObject Server::convertGameStateToJsonObject(GameState &obj)
{
    std::string text = getStringFromGameState(obj);
    QJsonDocument doc = QJsonDocument::fromJson(text.c_str());
    QJsonObject json_obj = doc.object();
    return json_obj;
}

std::string Server::getStringFromGameState(GameState &obj)
{
    std::string result = "{ \"gameObject\" : [";
    for(auto it = (obj.gameObjects).begin() ; it != (obj.gameObjects).end() ; it++)
    {
        std::vector<qreal> position = ((*it)->graphicsComponent)->getSizePositionOfObject();
        result += " { \"state\" : ";   result += std::to_string(static_cast<int> (((*it)->state)->type()));
        result += " , \"jumpState\" : ";   result += std::to_string(static_cast<int> (((*it)->jumpingState)->type()));
        result += " , \"positionx\" : ";   result += std::to_string(position[0]);
        result += " , \"positiony\" : ";   result += std::to_string(position[1]);
        result += " , \"score\" : ";   result += std::to_string((*it)->getScore());
        result += " } , ";
    }
    result = result.substr(0 , result.size()-2);
    result += "] , \"gems\" : [";

    for(auto it = (obj.gems).begin() ; it != (obj.gems).end() ; it++)
    {
        result += std::to_string((*it)->getIsOnScreen()) + " , ";
    }
    result = result.substr(0 , result.size()-2);
    result += "] , \"timer\" : " + std::to_string((obj.timer)->getTimeLeftInMilliSeconds()) + "}";

    return result;
}
