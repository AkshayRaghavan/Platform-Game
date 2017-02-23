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
  //  Q_OBJECT

public:
    virtual ~GameState(){}
    std::vector<GameObject*> gameObjects;
    std::vector< std::vector<Tile*> > tileMap;
    std::vector<Gem*> gems;
    QGraphicsScene *scene;
    GameState(std::vector<GameObject*>&, std::vector< std::vector<Tile*> >&, std::vector<Gem*>&);
    QGraphicsScene *getScene();
    std::vector<GameObject*> getGameObjects();
    std::vector< std::vector<Tile*> > getTileMap();
    std::vector<Gem*> getGems();
public slots:
    void update();
};

#endif // GAMESTATE_H
