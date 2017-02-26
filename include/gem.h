#ifndef GEM_H
#define GEM_H

#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include<QDebug>
#include <thread>


// A class for the graphics of the game objects
// Used as virtual functions
// And deriving QGraphicsPixmapItem for image of object

class Gem : public QGraphicsPixmapItem
{
protected:
    int pointValue;
public:
    virtual void drawGem(QGraphicsScene* scene) {}
    int getPointValue();
   // void remove(QGraphicsScene* scene);
};

#endif // GEM_H
