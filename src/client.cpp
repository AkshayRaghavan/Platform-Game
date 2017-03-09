#include "client.h"

QT_USE_NAMESPACE


Client::Client(QApplication* a ,int milliseconds_per_frame , QGraphicsScene *scene_local , InputHandler *view_local ,int screen_initial_width ,int screen_initial_height , QLabel* label , QObject *parent):
    app(a),
    millisecondsPerFrame(milliseconds_per_frame),
    screenWidth(screen_initial_width),
    screenHeight(screen_initial_height),
    label(label),
    QObject(parent)
{
    view = view_local;
    scene = scene_local;
    receivedNoOfPlayerFlag = false;
    isAcceptingGameState = false;
    noOfPlayers = 0;
    arrayIndexInGameObject = -1;
    createGamePointer = new ReadInput(scene_local , screen_initial_width , screen_initial_height);
    createGamePointer->setApp(app);
    createGamePointer->remoteIdentity = enumerator::Identity::CLIENT;
    gamePointer = NULL;
}

void Client::connectToServer(QUrl url_local , QGraphicsTextItem* client_message , QString name_local)
{
    name = name_local;
    clientLoadingMessage = client_message;
    qDebug() << url_local;
    url = url_local;
    connect(&clientWebSocket, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
        [=](QAbstractSocket::SocketError error){
                    qDebug() << clientWebSocket.errorString();
                    std::exit(EXIT_FAILURE);
    });
    connect(&clientWebSocket, &QWebSocket::connected, this, &Client::onConnected);
    connect(&clientWebSocket, &QWebSocket::disconnected, this, &Client::closed);

    clientWebSocket.open(url_local);
    qDebug() << "WebSocket client started at :" << url;
}

int Client::getArrayIndex()
{
    return arrayIndexInGameObject;
}

QWebSocket* Client::getClientWebSocket()
{
    return &clientWebSocket;
}

void Client::DisplayScore(QString result)
{

    foreach(QGraphicsItem *item, scene->items())
    {
        scene->removeItem(item);
    }

    QImage *back = new QImage("resources/images/assets/server client start button/background_score.png");
    if(back->isNull())
    {
        qDebug() << "ERROR(client.cpp) : Failed To Load Image : resources/images/assets/server client start button/background_score.png";
        std::exit(EXIT_FAILURE);
    }
    QImage *background = new QImage(back->scaled(screenWidth,screenHeight ,Qt::IgnoreAspectRatio,Qt::FastTransformation));
    QBrush *brush = new QBrush(*background);
    view->setBackgroundBrush(*brush);

    QGraphicsTextItem * winner = new QGraphicsTextItem;
    winner->setFont(QFont("comic sans",20));
    winner->setHtml(result);
    winner->setPos(view->width()/2 - winner->boundingRect().width()/2,view->height()/3);
    scene->addItem(winner);
}

void Client::onConnected()
{
    qDebug() << "Client WebSocket connected";
    connect(&clientWebSocket, &QWebSocket::textMessageReceived,this, &Client::onTextMessageReceived);
    connect(&clientWebSocket, &QWebSocket::binaryMessageReceived,this, &Client::onBinaryMessageReceived);
}

void Client::onTextMessageReceived(QString message)
{
    if(message.startsWith("<div"))
    {
        DisplayScore(message);
        return;
    }
    app->processEvents();
    clientLoadingMessage->setHtml(message);
    app->processEvents();
    qDebug() << " ********************* Message received from server :" << message;
}

void Client::onBinaryMessageReceived(QByteArray bytes)
{
    QJsonDocument itemDoc = QJsonDocument::fromJson(bytes);
    QJsonObject itemObject = itemDoc.object();

    if (!receivedNoOfPlayerFlag)
    {
        app->processEvents();
        clientLoadingMessage->setHtml("Received The Players Information From Server");
        app->processEvents();
        if((!itemObject.contains("noOfPeople")) || (!itemObject.contains("arrayIndex")))
        {
                qDebug() << "ERROR(client.cpp) : InCorrect JSON From Server Of NoOfPlayer , ArrayIndex";
                std::exit(EXIT_FAILURE);
        }
        noOfPlayers = itemObject["noOfPeople"].toInt();
        arrayIndexInGameObject = itemObject["arrayIndex"].toInt();
        qDebug() << "Initial Binary Message received: (noOfplayer : " << noOfPlayers << ") , (arrayIndexInGameObject : "<<arrayIndexInGameObject<<")";
        receivedNoOfPlayerFlag = true;
    }
    else if(!isAcceptingGameState)
    {
        app->processEvents();
        clientLoadingMessage->setHtml("Making The Game Screen");
        app->processEvents();
        qDebug() << "Making The Game Screen";
        setGameStartedVal();
    }
    else if(isAcceptingGameState)
    {
        if((!itemObject.contains("gameObject")) || (!itemObject.contains("gems")) || (!itemObject.contains("timer")))
        {
                qDebug() << "ERROR(client.cpp) : InCorrect JSON From Server Of gameObject , gems , timer";
                std::exit(EXIT_FAILURE);
        }
        QJsonArray json_array = itemObject["gameObject"].toArray();
        int counter_game = 0;
        foreach (const QJsonValue & value, json_array)
        {
            QJsonObject obj = value.toObject();
            (((gamePointer->gameObjects)[counter_game])->graphicsComponent)->setPos((obj["positionx"]).toDouble()*(createGamePointer->width_of_tile) , (obj["positiony"]).toDouble()*(createGamePointer->height_of_tile));

            if(((gamePointer->gameObjects)[counter_game])->scoreComponent)
            {
                (((gamePointer->gameObjects)[counter_game])->scoreComponent)->setPos((obj["positionx"]).toDouble()*(createGamePointer->width_of_tile) + (((gamePointer->gameObjects)[counter_game])->scoreComponent)->getscoreDisplayDiffX(),
                                                                                     (obj["positiony"]).toDouble()*(createGamePointer->height_of_tile) + (((gamePointer->gameObjects)[counter_game])->scoreComponent)->getscoreDisplayDiffY());
            }

            (((gamePointer->gameObjects)[counter_game]))->setScore((obj["score"]).toInt());

            enumerator::State client_gameobject_state = static_cast<enumerator::State>((obj["state"]).toInt());
            enumerator::JumpingState client_gameobject_jumpstate = static_cast<enumerator::JumpingState>((obj["jumpState"]).toInt());

            if(client_gameobject_state == enumerator::State::MOVING_RIGHT)
            {
                ((gamePointer->gameObjects)[counter_game])->setState(new MovingRight);
            }
            else if(client_gameobject_state == enumerator::State::MOVING_LEFT)
            {
                ((gamePointer->gameObjects)[counter_game])->setState(new MovingLeft);
            }
            else if(client_gameobject_state == enumerator::State::STOP_LEFT)
            {
                ((gamePointer->gameObjects)[counter_game])->setState(new StopLeft);
            }
            else if(client_gameobject_state == enumerator::State::STOP_RIGHT)
            {
                ((gamePointer->gameObjects)[counter_game])->setState(new StopRight);
            }
            else if(client_gameobject_state == enumerator::State::DEAD_LEFT)
            {
                ((gamePointer->gameObjects)[counter_game])->setState(new DeadLeft);
            }
            else if(client_gameobject_state == enumerator::State::DEAD_RIGHT)
            {
                ((gamePointer->gameObjects)[counter_game])->setState(new DeadRight);
            }

            if(client_gameobject_jumpstate == enumerator::JumpingState::IS_JUMPING)
            {
                ((gamePointer->gameObjects)[counter_game])->setJumpingState(new IsJumping(*((gamePointer->gameObjects)[counter_game])));
            }
            else if(client_gameobject_jumpstate == enumerator::JumpingState::IS_NOT_JUMPING)
            {
                ((gamePointer->gameObjects)[counter_game])->setJumpingState(new IsNotJumping);
            }
                    counter_game++;
         }

         json_array = itemObject["gems"].toArray();
         counter_game = 0;
         foreach (const QJsonValue & value, json_array)
         {
            ((gamePointer->gems)[counter_game++])->setIsOnScreen((value.toDouble() == 1)? true:false);
         }

         (gamePointer->timer)->setTimeLeft(itemObject["timer"].toInt());
         gamePointer->update();
    }
}

void Client::setGameStartedVal()
{
    startGame( "resources/game files/tile map level1/tile map level1.txt" ,
               "resources/game files/monster/monster level1.txt" ,
               "resources/game files/fire/fire level1.txt" ,
               "resources/game files/gems/diamond map level1.txt" ,
               "resources/game files/player/player level1.txt" ,
               "resources/game files/player/player level special.txt" ,
               "resources/game files/door/door.txt" ,
               "resources/images/bg2.png" , 60000);

}

void Client::startGame(std::string tile_map_path , std::string monster_file_path ,
                       std::string fire_file_path , std::string gem_path ,
                       std::string player_file_path , std::string player_special_path ,
                       std::string door_file_path , std::string bg_image_path ,
                       int total_time)
{

    app->processEvents();
    clientLoadingMessage->setHtml("Adding Tiles To Screen");
    app->processEvents();
    createGamePointer->functionToCreateTileMap(tile_map_path);

    app->processEvents();
    clientLoadingMessage->setHtml("Adding Gems To Screen");
    app->processEvents();
    createGamePointer->functionToCreateGem(gem_path);

    app->processEvents();
    clientLoadingMessage->setHtml("Adding Players To Screen");
    app->processEvents();

    for (int i = 0; i < noOfPlayers; i++)
    {
        if(i == arrayIndexInGameObject)
        {
            createGamePointer->functionToCreatePlayerGameObject(player_special_path);
        }
        else
        {
            createGamePointer->functionToCreatePlayerGameObject(player_file_path);
        }
    }

    app->processEvents();
    clientLoadingMessage->setHtml("Adding Monsters To Screen");
    app->processEvents();
    createGamePointer->functionToCreateMonsterGameObject(monster_file_path);

    app->processEvents();
    clientLoadingMessage->setHtml("Adding Fire To Screen");
    app->processEvents();
    createGamePointer->functionToCreateFireObject(fire_file_path);

    app->processEvents();
    clientLoadingMessage->setHtml("Adding Final Point To Screen");
    app->processEvents();
    createGamePointer->functionToCreateDoor(door_file_path);


    for(auto it = (createGamePointer->gems).begin(); it != (createGamePointer->gems).end() ; it++)
    {
        (*it)->drawGem(scene);
    }

    for(auto it = createGamePointer->gameObject.begin(); it != createGamePointer->gameObject.end() ; it++)
    {
        scene->addItem((*it)->graphicsComponent);
        if((*it)->scoreComponent)
        {
            scene->addItem((*it)->scoreComponent);
        }
    }
    createGamePointer->tileMap = std::vector< std::vector<Tile*> > (0);

    gamePointer = new GameState(createGamePointer->gameObject , createGamePointer->tileMap , createGamePointer->gems , screenWidth , screenHeight , scene , millisecondsPerFrame, total_time);
    gamePointer->remoteIdentity = enumerator::Identity::CLIENT;

    isAcceptingGameState = true;
    view->setGameState(gamePointer);

    app->processEvents();
    clientLoadingMessage->setHtml("Adding Background Imagee");
    app->processEvents();

    QImage *back = new QImage(bg_image_path.c_str());
    if(back->isNull())
    {
            qDebug() << "ERROR(client.cpp) -> File Not Found : "<< bg_image_path.c_str();
            std::exit(EXIT_FAILURE);
    }
    QImage *background = new QImage(back->scaled(screenWidth,screenHeight ,Qt::IgnoreAspectRatio,Qt::FastTransformation));
    QBrush *brush = new QBrush(*background);
    view->setBackgroundBrush(*brush);
    label->hide();

    clientLoadingMessage->setHtml("Pinging Server About Status<br>P.S. You Are The Brown Player");
    app->processEvents();
    QString message = "start="+QString::number(arrayIndexInGameObject)+"$"+name;
    clientWebSocket.sendTextMessage(message);

    app->processEvents();
    scene->removeItem(clientLoadingMessage);
    app->processEvents();
}
