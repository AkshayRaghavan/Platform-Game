#ifndef FIREGRAPHICSCOMPONENT_H
#define FIREGRAPHICSCOMPONENT_H

#include "graphicscomponent.h"
#include "gameobject.h"
#include <QGraphicsScene>
#include<QPixmap>
#include <QGraphicsTextItem>
#include<QDebug>
#include <string>

// A class for the graphics of the game objects
// Used as virtual functions
// And deriving QGraphicsPixmapItem for image of object

class FireGraphicsComponent : public GraphicsComponent
{
private:
    //A 2D array to contain pixmaps of all the images of a player (walk , jump , dead , idle) <right , left for each>
    QPixmap* pixMapArray;
    //Array for saving total images in a graphic state
    int imagesTotalCount;
    //Array for telling which image of each state to be displayed next
    int graphicsCounter;

public:
    FireGraphicsComponent(QGraphicsScene* scene ,  std::string images_location , int images_total_count, int image_width , int image_height , qreal x_coordinate , qreal y_coordinate);
    ~FireGraphicsComponent() {}
    //in each game loop this function is called which changes the image based on graphicsCounter[]
    void update(GameObject &obj);
};

#endif // FIREGRAPHICSCOMPONENT_H
