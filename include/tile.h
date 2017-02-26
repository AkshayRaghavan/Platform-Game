#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include <QPen>
#include <QGraphicsScene>

// A class for a tile rectangle
// Used for stopping player on obstacle detection

class Tile : public QGraphicsRectItem
{
private:
    bool isObstacle;
    int columnPosition;
    int rowPosition;
    int widthOfTile;
    int heightOfTile;
public:
    Tile(int left , int top , int width , int height , bool isObstacle);
    bool getIsObstacle();
    int getWidthOfTile();
    int getHeightOfTile();    
};

#endif // TILE_H
