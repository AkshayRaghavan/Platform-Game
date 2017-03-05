#include "server.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <QJsonObject>
#include <QTimer>
#include <QKeyEvent>
QT_USE_NAMESPACE

Server::Server(quint16 port, QGraphicsScene* scene_local , int screen_width ,
               int screen_height ,  int milliseconds_per_frame , QObject *parent) :
    QObject(parent),
    webSocketServer(new QWebSocketServer(QStringLiteral("Platform Game Server"),
                                         QWebSocketServer::NonSecureMode, this)),
    millisecondsPerFrame(milliseconds_per_frame)
{
    scene = scene_local;
    gameStartedCountOfClients = 0;
    maxConnectionsReached = false;
    gameStarted = false;

    qDebug() << "Creating Server";
    webSocketServer->setProxy(QNetworkProxy::NoProxy);
    createGamePointer = new ReadInput(scene,screen_width,screen_height);

    if (webSocketServer->listen(QHostAddress("0.0.0.0"), port)) {
        qDebug() << "Server Started";
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
    qDebug() << webSocketServer->serverUrl();

}

Server::~Server()
{
    webSocketServer->close();
    qDeleteAll(webSocketClients.begin(), webSocketClients.end());
}

void Server::onNewConnection()
{
    qDebug() << "Got A New Connection To Play Game";
    QWebSocket *pSocket = webSocketServer->nextPendingConnection();
    if(maxConnectionsReached)
    {
        pSocket->sendTextMessage("Game Has Started . Please Join Us For The Next Game.");
    }
    else
    {
        QObject::connect(pSocket, &QWebSocket::binaryMessageReceived, this, &Server::processBinaryMessage);
        QObject::connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processTextMessage);
        QObject::connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);
        webSocketClients << pSocket;
        pSocket->sendTextMessage("successfully connected. Waiting For Game To Start");
        qDebug() << "Added To webSocketClients And Sent Response Message";
        if(webSocketClients.size() == 1)
        {
            qDebug() << "Forming Game Screen";
            setGameStartedVal();
        }
    }
}

void Server::setGameStartedVal()
{
    maxConnectionsReached = true;
    startGame( "resources/game files/tile map level1/tile map level1.txt" ,
               "resources/game files/monster/monster level1.txt" ,
               "resources/game files/fire/fire level1.txt" ,
               "resources/game files/gems/diamond map level1.txt" ,
               "resources/game files/player/player level1.txt" ,
               "resources/game files/door/door.txt"
                , 60000);

}

void Server::startGame(std::string tile_map_path , std::string monster_file_path ,
                       std::string fire_file_path , std::string gem_path ,
                       std::string player_file_path ,
                       std::string door_file_path , int total_time)
{
    createGamePointer->functionToCreateTileMap(tile_map_path);
    createGamePointer->functionToCreateGem(gem_path);
    for (int i = 0; i != webSocketClients.size(); i++)
    {
        createGamePointer->functionToCreatePlayerGameObject(player_file_path);
    }

    createGamePointer->functionToCreateMonsterGameObject(monster_file_path);
    createGamePointer->functionToCreateFireObject(fire_file_path);
    createGamePointer->functionToCreateDoor(door_file_path);



    
    qDebug() << "Adding Gems To Scene";
    for(auto it = (createGamePointer->gems).begin(); it != (createGamePointer->gems).end() ; it++)
        (*it)->drawGem(scene);
        
    qDebug() << "Adding GameObjects To Scene";
    for(auto it = createGamePointer->gameObject.begin(); it != createGamePointer->gameObject.end() ; it++)
    {
        scene->addItem((*it)->graphicsComponent);
        /*if((*it)->scoreComponent)
        {
            scene->addItem((*it)->scoreComponent);
        }*/
    }
    
    
    gamePointer = new GameState(createGamePointer->gameObject , createGamePointer->tileMap , createGamePointer->gems , createGamePointer->screenWidth , createGamePointer->screenHeight , createGamePointer->scene , millisecondsPerFrame, total_time);

    QTimer * timer = new QTimer();
    gamePointer->connect(timer,SIGNAL(timeout()), gamePointer ,SLOT(update()));
    timer->start(40);

    sendIndexToCLient();
}


void Server::sendIndexToCLient()
{
    QJsonObject object;
    object.insert ("noOfPeople" , QJsonValue(webSocketClients.size()));
    object.insert ("arrayIndex" , -1);
    int loop_count_client = 0;
    for (int i = 0; i != (gamePointer->gameObjects).size(); i++)
    {
        if(((((gamePointer->gameObjects)[i])->graphicsComponent)->getIsDangerous()) == false)
        {
            object["arrayIndex"] = i;
            QJsonDocument doc(object);
            QByteArray bytes = doc.toJson();
            webSocketClients[loop_count_client++]->sendBinaryMessage(bytes);
        }
    }
    qDebug() << "Sent Index To Client";
    object = convertGameStateToJsonObject(*gamePointer);
    QJsonDocument doc(object);
    QByteArray bytes = doc.toJson();

    for (QList<QWebSocket*>::iterator i = webSocketClients.begin(); i != webSocketClients.end(); i++)
    {
        (*i)->sendBinaryMessage(bytes);
    }
}

void Server::startServerGameLoop()
{
    QTimer * timer = new QTimer();
    this->connect(timer,SIGNAL(timeout()),this,SLOT(iterateOverGameState()));
    timer->start(50);
    qDebug() << "Started Game Loop";
}

void Server::iterateOverGameState()
{
    QJsonObject object = convertGameStateToJsonObject(*gamePointer);
    QJsonDocument doc(object);
    QByteArray bytes = doc.toJson();
    qDebug() << "SENDING";

    for (QList<QWebSocket*>::iterator i = webSocketClients.begin(); i != webSocketClients.end(); i++)
    {
        (*i)->sendBinaryMessage(bytes);
    }
}

void Server::processTextMessage(QString message)
{
    if(message == "start")
    {
        qDebug() << "Received client start";
        gameStartedCountOfClients++;
        if(gameStartedCountOfClients == webSocketClients.size())
        {
            gameStarted = true;
            startServerGameLoop();
        }
    }
}
void Server::processBinaryMessage(QByteArray message)
{
    qDebug() << "Client Key Press EVent Message received";
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
            qDebug() << "UP keypress";
            event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Up , Qt::NoModifier);
        }
        else if(key == "LEFT")
        {
            qDebug() << "LEFT keypress";
            event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Left , Qt::NoModifier);
        }
        else if(key == "RIGHT")
        {
            qDebug() << "RIGHT keypress";
            event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Right , Qt::NoModifier);
        }
    }
    else if(eventName == "keyrelease")
    {
        if(key == "UP")
        {
            qDebug() << "UP keyrelease";
            event = new QKeyEvent ( QEvent::KeyRelease, Qt::Key_Up , Qt::NoModifier);
        }
        else if(key == "LEFT")
        {
            qDebug() << "LEFT keyrelease";
            event = new QKeyEvent ( QEvent::KeyRelease, Qt::Key_Left , Qt::NoModifier);
        }
        else if(key == "RIGHT")
        {
            qDebug() << "RIGHT keyrelease";
            event = new QKeyEvent ( QEvent::KeyRelease, Qt::Key_Right , Qt::NoModifier);
        }
    }
    QCoreApplication::sendEvent(gamePointer->gameObjects[array_index] , event);
    qDebug() << "Event Posted";
}

void Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        if (webSocketClients.removeAll(pClient) == 1)
        {
            qDebug() << "Deleted Client From List";
        }
        else
        {
            qDebug() << "Error In Deleteing Client";
            std::exit(EXIT_FAILURE);
        }
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
        result += std::to_string(((*it)->getIsOnScreen())? 1:0) + " , ";
    }
    result = result.substr(0 , result.size()-2);
    result += "] , \"timer\" : " + std::to_string((obj.timer)->getTimeLeftInMilliSeconds()) + "}";

    return result;
}
