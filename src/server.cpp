#include"server.h"

QJsonObject Server::convertGameStateToJsonObject(GameState &obj)
{
    std::string text = getStringFromGameState(obj);
    QJsonDocument doc = QJsonDocument::fromJson(text.c_str());
    QJsonObject json_obj = doc.object();
    return json_obj;
}

std::string Server::getStringFromGameState(GameState &obj)
{
    std::string result = "{ \"gamestate\" : [";
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

//TODO
/*

std::string Server::setGameStateFromJsonObject(QJsonObject & json_obj , GameState &obj)
{
    QJsonArray array = json_obj["gamestate"].toArray();
    return result;
}

*/
