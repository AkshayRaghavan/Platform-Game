#include "server.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <QJsonObject>
#include <QTimer>
#include <QKeyEvent>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <sstream>
#include <QThread>
QT_USE_NAMESPACE

Server::Server(quint16 port, QApplication * a , QGraphicsScene* scene_local , int milliseconds_per_frame , int number_of_threads , QLabel* label , QObject *parent) :
    app(a),
    port(port),
    QObject(parent),
    webSocketServer( new QWebSocketServer(QStringLiteral("Platform Game Server"), QWebSocketServer::NonSecureMode, this)),
    millisecondsPerFrame(milliseconds_per_frame),
    threadPool(number_of_threads), threadPool2(number_of_threads),
    label(label)
{
    webSocketServer->setProxy(QNetworkProxy::NoProxy);
    scene = new QGraphicsScene;
    gameStartedCountOfClients = 0;
    maxConnectionsReached = false;
    gameStarted = false;
}

void Server::startServer(int screen_width , int screen_height)
{
    qDebug() << "Creating Server";
    createGamePointer = new ReadInput(scene,screen_width,screen_height);
    createGamePointer->remoteIdentity = enumerator::Identity::SERVER;
    if (webSocketServer->listen(QHostAddress("0.0.0.0"), port))
    {
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
    qDebug() << "Server's connecting URL : " << webSocketServer->serverUrl();
}

Server::~Server()
{
    webSocketServer->close();
    qDeleteAll(webSocketClients.begin(), webSocketClients.end());
}

void Server::setClientIPList(QGraphicsTextItem* client_IP_list)
{
    clientIPList = client_IP_list;
}

void Server::onNewConnection()
{
    qDebug() << "Got A New Connection To Play Game";
    std::condition_variable cv;
    std::mutex mutex;

    if(maxConnectionsReached)
    {
        QWebSocket *pSocket = webSocketServer->nextPendingConnection();
        pSocket->sendTextMessage("The Game Has Already Started . <br>Please Join Us For The Next Game.");
    }
    else
    {
        QWebSocket *pSocket = webSocketServer->nextPendingConnection();
        QObject::connect(pSocket, &QWebSocket::binaryMessageReceived, this, &Server::processBinaryMessage,Qt::DirectConnection);
        QObject::connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processTextMessage,Qt::DirectConnection);
        QObject::connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected,Qt::DirectConnection);

        webSocketClients << pSocket;
        pSocket->sendTextMessage("successfully connected. <br>Waiting For Other Players To Join");
        qDebug() << "Added To webSocketClients And Sent Response Message";
        qDebug() << "websize: " << webSocketClients.size();
        qDebug() << "last but two";
        clientIPList->setHtml(QString("<br><br>")+clientIPList->toPlainText() + QString("<br><br>Player #"+QString::number(webSocketClients.size())+"&nbsp;&nbsp;&nbsp;&nbsp;").append(pSocket->requestUrl().toString()));
    }
        qDebug() << "websize: " << webSocketClients.size();
        qDebug() << "last but two";
    qDebug() << "last but one";
}

void Server::startGameSlotButtonClick(QGraphicsTextItem* server_message)
{
    if(webSocketClients.size() == 0)
    {
        qDebug() << "(server.cpp) NO CLIENTS TO PLAY WITH.";
        std::exit(EXIT_SUCCESS);
    }
    serverLoadingMessage = server_message;
    maxConnectionsReached = true;
    qDebug() << "Forming Game Screen";
    app->processEvents();
    serverLoadingMessage->setHtml("Forming Game Screen");
    app->processEvents();
    setGameStartedVal();
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
    createGamePointer->totalTime = total_time;
    app->processEvents();
    serverLoadingMessage->setHtml("Creating Tiles");
    app->processEvents();
    createGamePointer->functionToCreateTileMap(tile_map_path);

    app->processEvents();
    serverLoadingMessage->setHtml("Creating The Gems");
    app->processEvents();
    createGamePointer->functionToCreateGem(gem_path);

    app->processEvents();
    serverLoadingMessage->setHtml("Adding The Players On the Screen");
    app->processEvents();

    for (int i = 0; i < webSocketClients.size(); i++)
    {
        createGamePointer->functionToCreatePlayerGameObject(player_file_path);
    }

    app->processEvents();
    serverLoadingMessage->setHtml("Adding The Monsters On the Screen");
    app->processEvents();
    createGamePointer->functionToCreateMonsterGameObject(monster_file_path);

    app->processEvents();
    serverLoadingMessage->setHtml("Adding The Fire On the Screen");
    app->processEvents();
    createGamePointer->functionToCreateFireObject(fire_file_path);

    app->processEvents();
    serverLoadingMessage->setHtml("Adding The Final Point On the Screen");
    app->processEvents();
    createGamePointer->functionToCreateDoor(door_file_path);



    qDebug() << "Adding Gems To Scene";

    for(auto it = (createGamePointer->gems).begin(); it != (createGamePointer->gems).end() ; it++)
        (*it)->drawGem(scene);

    qDebug() << "Adding GameObjects To Scene : "<< createGamePointer->gameObject.size();
    for(auto it = createGamePointer->gameObject.begin(); it != createGamePointer->gameObject.end() ; it++)
    {
        scene->addItem((*it)->graphicsComponent);
    }

    gamePointer = new GameState(createGamePointer->gameObject , createGamePointer->tileMap , createGamePointer->gems , createGamePointer->screenWidth , createGamePointer->screenHeight , createGamePointer->scene , millisecondsPerFrame, total_time);
    gamePointer->remoteIdentity = enumerator::Identity::SERVER;
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
    app->processEvents();
    serverLoadingMessage->setHtml("Sending Player Information To Clients");
    app->processEvents();
    qDebug() << "Sent Index To Client";
    object = convertGameStateToJsonObject(*gamePointer);
    QJsonDocument doc(object);
    QByteArray bytes = doc.toJson();
    for (QList<QWebSocket*>::iterator i = webSocketClients.begin(); i != webSocketClients.end(); i++)
    {
         qDebug() << "Sent Index To Client";
        (*i)->sendBinaryMessage(bytes);
    }
    app->processEvents();
    serverLoadingMessage->setHtml("Waiting For Client Ready Response.");
    app->processEvents();
}

void Server::startServerGameLoop()
{
    serverLoopRunning = true;
    app->processEvents();
    serverLoadingMessage->setHtml("Starting The Server Game Loop");
    app->processEvents();
    qDebug() << "starting game loop";
    QTimer * timer = new QTimer();
    this->connect(timer,SIGNAL(timeout()),this,SLOT(iterateOverGameState()));
    timer->start(50);
    qDebug() << "Started Game Loop";
    app->processEvents();
    serverLoadingMessage->setHtml("The Game Has Started !!!");
    label->hide();
    app->processEvents();
}

void Server::iterateOverGameState()
{
    if(!serverLoopRunning)
    {
        return;
    }
    if( !gamePointer->isGameActive())
    {
        getLeaderBoard();
        serverLoopRunning = false;
    }
    gamePointer->update();
    QJsonObject object = convertGameStateToJsonObject(*gamePointer);
    QJsonDocument doc(object);
    QByteArray bytes = doc.toJson();
    std::vector<std::thread> client_threads;
    for (QList<QWebSocket*>::iterator i = webSocketClients.begin(); i != webSocketClients.end(); i++)
    {
     /*   QWebSocket *socket = *i;
        qDebug() << "socket outside: " << socket;
        std::function<void()> pass_func = [bytes,socket,this]() {
             if(!socket) { qDebug() << "null socket"; }
              else { qDebug() << "socket not null"; }
            qDebug() << "inside!";
            qDebug() << "socket inside: " << socket;*/
          (*i)->sendBinaryMessage(bytes);

      //  };
      //  threadPool.assignToThread(pass_func );
    }
}

void Server::processTextMessage(QString message)
{
    if(message.startsWith("start"))
    {
        //start=0$typo
        bool check;
        int index = (message.mid( message.indexOf("=")+1 , message.indexOf("$") - message.indexOf("=") - 1)).toInt(&check , 10);
        qDebug() << index;
        QString a = message.mid(message.indexOf("$")+1);
        (gamePointer->gameObjects[index])->setName(a);
        gameStartedCountOfClients++;
        qDebug() << "Received client start" << message << " " << gameStartedCountOfClients << " " << webSocketClients.size();
        if(gameStartedCountOfClients == webSocketClients.size())
        {
            gameStarted = true;
            startServerGameLoop();
        }
    }
}
void Server::getLeaderBoard()
{
    std::vector <std::tuple<QString , int , int, int>> leader_board;
    for (int i = 0; i < (gamePointer->gameObjects).size(); i++)
    {
        if(((((gamePointer->gameObjects)[i])->graphicsComponent)->getIsDangerous()) == false)
        {
            if(!((gamePointer->gameObjects)[i])->isAcceptingInput())
            {
                leader_board.push_back(std::make_tuple(((gamePointer->gameObjects)[i])->getName()  , ((gamePointer->gameObjects)[i])->getScore() , createGamePointer->totalTime - ((gamePointer->gameObjects)[i])->getTimeLeft() , ((gamePointer->gameObjects)[i])->getScore() + ((gamePointer->gameObjects)[i])->getTimeLeft()));
            }
            else
            {
                leader_board.push_back(std::make_tuple(((gamePointer->gameObjects)[i])->getName()  , ((gamePointer->gameObjects)[i])->getScore() , 0 , -1));
            }
        }
    }
    std::sort(leader_board.begin(), leader_board.end(), [](auto &left, auto &right) {
        return std::get<3>(left) > std::get<3>(right);
    });

    QString result("<div  style='color:red;'><table><thead><tr><strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SCOREBOARD<br><br>Rank&nbsp;&nbsp;&nbsp;Player Name&nbsp;&nbsp;&nbsp;Gems&nbsp;Score&nbsp;&nbsp;&nbsp;Time&nbsp;Taken&nbsp;&nbsp;&nbsp;Total&nbsp;score<br><br></strong>");

    for (int i = 1; i <= leader_board.size(); i++)
    {
        result += "<strong>" + QString::number(i) + "</strong>&nbsp;&nbsp;&nbsp;" +  std::get<0>(leader_board[i-1]) + "&nbsp;&nbsp;&nbsp;" + QString::number(std::get<1>(leader_board[i-1])) + "&nbsp;&nbsp;&nbsp;" + QString::number(std::get<2>(leader_board[i-1])) + "&nbsp;&nbsp;&nbsp;" + QString::number(std::get<3>(leader_board[i-1])) + "<br>";
    }
    result += "</div>";
    app->processEvents();
    serverLoadingMessage->setHtml(result);
    app->processEvents();

    for (QList<QWebSocket*>::iterator i = webSocketClients.begin(); i != webSocketClients.end(); i++)
    {
        (*i)->sendTextMessage(result);
    }
}
void Server::processBinaryMessage(QByteArray message)
{
    qDebug() << "creating thread";

    threadPool.assignToThread([=](){
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

                std::stringstream ss;
                ss<<std::this_thread::get_id();
                std::string id_str=ss.str();

            qDebug() << "RIGHT keypress" << id_str.c_str();
               qDebug() << QThread::currentThreadId();
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
    qDebug() << "event ready" << array_index;
    if((gamePointer->gameObjects[array_index])->inputComponent)
    {
        qDebug() << "the problem is not null pointer";
    }
    if(!event)
    {
        qDebug() << "event is NULL";
    }
    QCoreApplication::postEvent((gamePointer->gameObjects[array_index])->inputComponent , event);
    qDebug() << "Event Posted";
   });
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
        result += " , \"positionx\" : ";   result += std::to_string(position[0]/(createGamePointer->width_of_tile));
        result += " , \"positiony\" : ";   result += std::to_string(position[1]/(createGamePointer->height_of_tile));
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
