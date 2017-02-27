#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <QObject>
#include <QGraphicsScene>
#include "gameobject.h"
#include <thread>
#include "tile.h"
#include "gem.h"

class GameState : public QObject
{
    Q_OBJECT
private:
    void parallel(bool isAcceptingInput , GameObject * player_ptr , bool *someone_accepting_input);

public:
    bool isGameRunning;
    GameState(std::vector<GameObject*> &game_objects, std::vector< std::vector<Tile*> > &tile_map, std::vector<Gem*> &input_gems , int screen_width , int screen_height , QGraphicsScene* scene);
    virtual ~GameState(){}
    std::vector<GameObject*> gameObjects;
    std::vector< std::vector<Tile*> > tileMap;
    std::vector<Gem*> gems;
    QGraphicsScene *scene;
    const int screenWidth;
    const int screenHeight;
    QGraphicsScene* getScene();
    bool isGameActive();
    std::vector<GameObject*> getGameObjects();
    std::vector< std::vector<Tile*> > getTileMap();
    std::vector<Gem*> getGems();
    void setPosition(int,qreal,qreal);
    void setPixMapValue(int,int);
    void removeObject(int);
//    void setTimerAndConnect(QTimer *);

public slots:
    void update();

};

#endif // GAMESTATE_H
