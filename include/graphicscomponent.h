#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

class GameObject;
#include<QGraphicsPixmapItem>

class GraphicsComponent : public QGraphicsPixmapItem
{
     Q_OBJECT
public:
    GraphicsComponent();
    virtual ~GraphicsComponent() {}
    virtual void update(GameObject &) {}
};


#endif // GRAPHICSCOMPONENT_H

