#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

class GameObject;
#include<QGraphicsPixmapItem>
#include<QGraphicsTextItem>
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
    virtual bool getIsMonster() = 0;
    virtual std::vector<qreal> getSizePositionOfObject() {}
    virtual void setPosScorePointer( int going_to_x , int going_to_y ){}
};


#endif // GRAPHICSCOMPONENT_H

