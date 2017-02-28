#ifndef SERVER_H
#define SERVER_H
#include<QJsonDocument>
#include<QJsonObject>
#include "gamestate.h"

class Server
{
public:
    QJsonObject convertGameStateToJsonObject(GameState &);
    std::string getStringFromGameState(GameState &);

};
#endif // SERVER_H
