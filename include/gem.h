#ifndef GEM_H
#define GEM_H

#include "graphicscomponent.h"
#include "enumerator.h"
#include "state.h"
#include "jumpingstate.h"
#include "gameobject.h"
#include<QGraphicsScene>
#include<QDebug>

#define NO_Of_GRAPHICS_STATES 8

// A class for the graphics of the game objects
// Used as virtual functions
// And deriving QGraphicsPixmapItem for image of object

class Gem : public GraphicsComponent
{
private:
    int pointValue;
    QGraphicsScene* scene;

public:
    virtual void draw(GameObject &) {}

    inline int getPointValue();
    inline void setPointValue(int pointValue);

    inline QGraphicsScene* getQGraphicsScene();
    inline void setQGraphicsScene(QGraphicsScene* scene);

    void remove(QGraphicsScene* scene);
};

#endif // GEM_H
