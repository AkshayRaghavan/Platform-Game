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
protected:
    bool isDangerous;
    QGraphicsScene *scene;
public:
    GraphicsComponent(){}
    ~GraphicsComponent() {}
    virtual void update(GameObject &) {}
    bool getIsDangerous();
    QGraphicsScene * getQGraphicsScene();
    virtual std::vector<qreal> getSizePositionOfObject() {return std::vector<qreal>(1);}
    virtual void setPosScorePointer( int , int ){}
};


#endif // GRAPHICSCOMPONENT_H
