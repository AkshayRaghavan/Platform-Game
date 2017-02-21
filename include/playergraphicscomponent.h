#ifndef PLAYERGRAPHICSCOMPONENT_H
#define PLAYERGRAPHICSCOMPONENT_H

#include<QPixmap>
#include<QDebug>
#include <cstdlib>
#include "graphicscomponent.h"

#define NO_Of_GRAPHICS_STATES 8

class GameObject;

class PlayerGraphicsComponent : public GraphicsComponent
{
private:
    QPixmap* pixMapMatrix[NO_Of_GRAPHICS_STATES];
    int imagesMaxCount[NO_Of_GRAPHICS_STATES];
    int graphicsCounter[NO_Of_GRAPHICS_STATES];
    int updateGraphicsCounter(int index  , GameObject * obj = NULL);
    void initializePixMaps(int upper_limit , std::string image_location , QPixmap* array_of_pixmaps , int scaling_factor);

public:
    PlayerGraphicsComponent(int images_max_count[] , std::string images_location);
    ~PlayerGraphicsComponent() {}
    void update(GameObject &);
};



#endif // PLAYERGRAPHICSCOMPONENT_H
