#ifndef FIREGRAPHICSCOMPONENT_H
#define FIREGRAPHICSCOMPONENT_H

#include "graphicscomponent.h"
#include "gameobject.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsTextItem>
#include<QDebug>
#include <string>
#include <QApplication>
#include <vector>

// A class for the graphics of the game objects
// Used as virtual functions
// And deriving QGraphicsPixmapItem for image of object

class FireGraphicsComponent : public GraphicsComponent
{
private:
    QApplication * app;
    //A 2D array to contain pixmaps of all the images of a player (walk , jump , dead , idle) <right , left for each>
    QPixmap* pixMapArray;
    //Array for saving total images in a graphic state
    int imagesTotalCount;
    //Array for telling which image of each state to be displayed next
    int graphicsCounter;

public:
    FireGraphicsComponent(QGraphicsScene* , std::string , int , int  , int  , qreal  , qreal , QApplication *);
    ~FireGraphicsComponent() {}
    //in each game loop this function is called which changes the image based on graphicsCounter[]
    void update(GameObject &obj);
    std::vector<qreal> getSizePositionOfObject();

};

#endif // FIREGRAPHICSCOMPONENT_H
