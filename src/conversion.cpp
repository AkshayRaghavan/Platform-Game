#include "conversion.h"

std::string Conversion::createStringFromData()
{
    std::string ans = to_string(first) + "$" + to_string(second) + "$" + to_string(third) + "$" + to_string(fourth) + "$" + to_string(fifth) + "$";
    return  ans;
}

QJsonObject Conversion::convertStringToJsonObject(std::string x)
{
    QJsonObject json;
    std::string str2 = "";
    
    int position_of_delimiter = x.find("$") , position_of_delimiter_temp = 0 ;

    str2 = x.substr (position_of_delimiter_temp , position_of_delimiter - position_of_delimiter_temp);
    position_of_delimiter_temp = position_of_delimiter;
    json.insert("first" , QJsonValue(std::stoi(str2)));
    
    position_of_delimiter = x.find("$" , position_of_delimiter+1);
    str2 = x.substr (position_of_delimiter_temp + 1, position_of_delimiter - position_of_delimiter_temp - 1);
    position_of_delimiter_temp = position_of_delimiter;
    json.insert("second" , QJsonValue(std::stof(str2)));
    
    position_of_delimiter = x.find("$" , position_of_delimiter+1);
    str2 = x.substr (position_of_delimiter_temp + 1, position_of_delimiter - position_of_delimiter_temp - 1);
    position_of_delimiter_temp = position_of_delimiter;
    json.insert("third" , QJsonValue(std::stof(str2)));
    
    position_of_delimiter = x.find("$" , position_of_delimiter+1);
    str2 = x.substr (position_of_delimiter_temp + 1, position_of_delimiter - position_of_delimiter_temp - 1);
    position_of_delimiter_temp = position_of_delimiter;
    json.insert("fourth" , QJsonValue(std::stoi(str2)));
    
    position_of_delimiter = x.find("$" , position_of_delimiter+1);
    str2 = x.substr (position_of_delimiter_temp + 1, position_of_delimiter - position_of_delimiter_temp - 1);
    json.insert("fifth" , QJsonValue( (str2 == "1")? true : false));
    
    return  json;
}

std::string Conversion::convertJsonObjectToString(QJsonObject x)
{
    std::string ans = x["first"].toString() + "$" + x["second"].toString() + "$" + x["third"].toString() + "$" + x["fourth"].toString() + "$" + x["fifth"].toString() + "$";
    return ans;
}

