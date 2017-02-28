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
    Diamond(std::string , int , int , qreal , qreal , int);
    void drawGem(QGraphicsScene* );
};

#endif // DIAMOND_H
