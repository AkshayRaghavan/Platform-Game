#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

class GameObject;
#include "tile.h"
#include <QGraphicsScene>

class PhysicsComponent : public QObject
{
    Q_OBJECT
protected:
    int velocity,acceleration;
    int newx,newy;
    std::vector<std::vector<Tile*> > tilesMap;
    QGraphicsScene * scene;
    int width_of_tile,height_of_tile,screenWidth,screenHeight;
    int curJumpCount,maxJumpCount;
signals:
    void setPosition(GameObject &, QPointF &);
    void removeObject(QGraphicsItem &);
public:
    PhysicsComponent() {};
    virtual ~PhysicsComponent() {};
    virtual void update (GameObject &) = 0;
    bool inRange(QPointF);
    bool testPoint(QPointF);
    bool testPositionForPlayer(QPointF, qreal, qreal);
    bool hasNoPlatformUnder(GameObject &);
    bool hasObstacleInFront(GameObject &);
};

#endif // PHYSICSCOMPONENT_H
