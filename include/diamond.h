#ifndef DIAMOND_H
#define DIAMOND_H

#include "gem.h"
#include <QPixmap>

#define NO_Of_GRAPHICS_STATES 8

// A class for the graphics of the game objects
// Used as virtual functions
// And deriving QGraphicsPixmapItem for image of object

class Diamond : public Gem
{
private:
    QPixmap pixMapImage;
public:
    Diamond(QGraphicsScene* scene_local , std::string image_location , int width , int height , qreal x_coordinate , qreal y_coordinate);
    void draw();
};

#endif // DIAMOND_H
