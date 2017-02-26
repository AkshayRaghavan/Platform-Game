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
    int updateGraphicsCounter(int index  , GameObject * obj = NULL);
    //used in the constructor
    void initializePixMaps(int images_total_count , std::string image_location ,  QPixmap* array_of_pixmaps , const int image_width , const int image_height);

public:
    //function to return left top coordinate and width and height of rectangle
    std::vector<qreal> getSizePositionOfObject();
    PlayerGraphicsComponent(QGraphicsScene* scene_formal_arg , std::string images_location , std::vector<int> &images_total_count, int image_width , int image_height , qreal x_coordinate , qreal y_coordinate , bool is_dangerous);
    ~PlayerGraphicsComponent() {}
    //in each game loop this function is called which changes the image based on graphicsCounter[]
    void update(GameObject &);
};

#endif // PLAYERGRAPHICSCOMPONENT_H
