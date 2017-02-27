#ifndef CONVERSION_H
#define CONVERSION_H

#include <QJsonObject>
#include <string>

class Conversion 
{
public:
    int first;
    qreal second;
    qreal third;
    int fourth;
    bool fifth;
    std::string combinationString;
    QJsonObject combinationJson;
    std::string createStringFromData();
    std::string convertJsonObjectToString(QJsonObject x);
    QJsonObject convertStringToJsonObject(std::string x);
};

#endif // GAMESTATE_H
