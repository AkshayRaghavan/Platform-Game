#ifndef GEMTYPE1_H
#define GEMTYPE1_H

#include "gem.h"
#include <QPixmap>

#define NO_Of_GRAPHICS_STATES 8

// A class for the graphics of the game objects
// Used as virtual functions
// And deriving QGraphicsPixmapItem for image of object

class GemType1 : public Gem
{
private:
    QPixmap pixMapImage;
public:
    GemType1(std::string images_location , int scaling_factor);
    void draw();
};

#endif // GEMTYPE1_H
