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
    bool isDangerous;
    int columnPosition;
    int rowPosition;
    int widthOfTile;
    int heightOfTile;
    QGraphicsRectItem* r;
public:
    Tile(QGraphicsScene* scene , int left , int top , int width , int height , bool isObstacle, bool isDangerous);
    QGraphicsRectItem* getR();
    bool getIsObstacle();
    int getWidthOfTile();
    int getHeightOfTile();
    bool getIsDangerous();
    
};

#endif // TILE_H
