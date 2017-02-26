#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

class GameObject;
#include<QGraphicsPixmapItem>
#include<QGraphicsTextItem>
#include<QObject>
#include<QPixmap>

// A class for the graphics of the game objects
// Used as virtual functions
// And deriving QGraphicsPixmapItem for image of object

class GraphicsComponent : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    bool isDangerous;
    QGraphicsScene *scene;
signals:
    void setPixMapValue(GraphicsComponent *,QPixmap );
public:
    GraphicsComponent(){}
    ~GraphicsComponent() {}
    virtual void update(GameObject &) {}
    bool getIsDangerous();
    QGraphicsScene * getQGraphicsScene();
    virtual std::vector<qreal> getSizePositionOfObject() {}
};


#endif // GRAPHICSCOMPONENT_H
