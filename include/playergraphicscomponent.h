#ifndef PLAYERGRAPHICSCOMPONENT_H
#define PLAYERGRAPHICSCOMPONENT_H

#include "graphicscomponent.h"
#include "enumerator.h"
#include "state.h"
#include "jumpingstate.h"
#include "gameobject.h"
#include <QGraphicsScene>
#include<QPixmap>
#include<QDebug>
#include<vector>
#include <string>

#define NO_Of_GRAPHICS_STATES 8

// A class for the graphics of the game objects
// Used as virtual functions
// And deriving QGraphicsPixmapItem for image of object

class PlayerGraphicsComponent : public GraphicsComponent
{
private:
    //A 2D array to contain pixmaps of all the images of a player (walk , jump , dead , idle) <right , left for each>
    std::vector<QPixmap*> pixMapMatrix;
    //Array for saving total images in a graphic state
    std::vector<int> imagesTotalCount;
    //Array for telling which image of each state to be displayed next
    std::vector<int> graphicsCounter;
    int updateGraphicsCounter(int   , GameObject * obj = NULL);
    //used in the constructor
    void initializePixMaps(int  , std::string  ,  QPixmap*  , const int  , const int );

public:
    //function to return left top coordinate and width and height of rectangle
    std::vector<qreal> getSizePositionOfObject();
    PlayerGraphicsComponent(QGraphicsScene* , std::string  , std::vector<int> &, int  , int  , qreal  , qreal  , bool );
    ~PlayerGraphicsComponent() {}
    //in each game loop this function is called which changes the image based on graphicsCounter[]
    void update(GameObject &);
};

#endif // PLAYERGRAPHICSCOMPONENT_H
