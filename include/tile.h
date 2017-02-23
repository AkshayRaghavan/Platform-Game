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
    int left_position;
    int top_position;
    int widthOfTile;
    int heightOfTile;
    QGraphicsRectItem* r;
public:
    Tile(QGraphicsScene* scene , int left , int top , int width , int height , bool isObstacle);
    QGraphicsRectItem* getR();
    bool getIsObstacle();
    int getWidthOfTile();
    int getHeightOfTile();
    
};

#endif // TILE_H
