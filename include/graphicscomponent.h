#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

class GameObject;
#include<QGraphicsPixmapItem>
#include<QObject>

// A class for the graphics of the game objects
// Used as virtual functions
// And deriving QGraphicsPixmapItem for image of object

class GraphicsComponent : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GraphicsComponent(){}
    ~GraphicsComponent() {}
    virtual void update(GameObject &) {}
    virtual bool getIsMonster() {}
    virtual std::vector<qreal> getSizePositionOfObject() {}
};


#endif // GRAPHICSCOMPONENT_H

