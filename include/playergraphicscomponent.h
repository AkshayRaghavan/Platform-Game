#ifndef PLAYERGRAPHICSCOMPONENT_H
#define PLAYERGRAPHICSCOMPONENT_H

#include<QPixmap>
#include<QDebug>
#include <cstdlib>
#include "include/graphicscomponent.h"
#define NO_Of_GRAPHICS_STATES 8

#define GRAPHICS_DEAD_LEFT 0
#define GRAPHICS_DEAD_RIGHT 1

#define GRAPHICS_IDLE_LEFT 2
#define GRAPHICS_IDLE_RIGHT 3

#define GRAPHICS_JUMP_LEFT 4
#define GRAPHICS_JUMP_RIGHT 5

#define GRAPHICS_WALK_LEFT 6
#define GRAPHICS_WALK_RIGHT 7

class GameObject;

class PlayerGraphicsComponent : public GraphicsComponent
{
private:
    QPixmap* pixMapMatrix[NO_Of_GRAPHICS_STATES];
    int imagesMaxCount[NO_Of_GRAPHICS_STATES];
    int graphicsCounter[NO_Of_GRAPHICS_STATES];
    int updateGraphicsCounter(int index);
    void initializePixMaps(int upper_limit , std::string image_location , QPixmap* array_of_pixmaps , int scaling_factor);

public:
    PlayerGraphicsComponent(int images_max_count[] , std::string images_location[]);
    ~PlayerGraphicsComponent() {}
    void update(GameObject &);
};



#endif // PLAYERGRAPHICSCOMPONENT_H
