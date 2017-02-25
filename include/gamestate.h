#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <QObject>
#include <QGraphicsScene>
#include "gameobject.h"
#include "tile.h"
#include "gem.h"

class GameState : public QObject
{
    Q_OBJECT
public:
    GameState(std::vector<GameObject*> &game_objects, std::vector< std::vector<Tile*> > &tile_map, std::vector<Gem*> &input_gems , int screen_width , int screen_height , QGraphicsScene* scene);
    virtual ~GameState(){}
    std::vector<GameObject*> gameObjects;
    std::vector< std::vector<Tile*> > tileMap;
    std::vector<Gem*> gems;
    QGraphicsScene *scene;
    const int screenWidth;
    const int screenHeight;
    QGraphicsScene* getScene();

    std::vector<GameObject*> getGameObjects();
    std::vector< std::vector<Tile*> > getTileMap();
    std::vector<Gem*> getGems();
//    void setTimerAndConnect(QTimer *);

public slots:
    void update();
};

#endif // GAMESTATE_H
