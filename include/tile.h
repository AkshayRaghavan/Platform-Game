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
    qreal columnPosition;
    qreal rowPosition;
    qreal widthOfTile;
    qreal heightOfTile;
    QGraphicsRectItem* r;
public:
    Tile(QGraphicsScene* scene , qreal left , qreal top , qreal width , qreal height , bool isObstacle);
    QGraphicsRectItem* getR();
    bool getIsObstacle();
    qreal getWidthOfTile();
    qreal getHeightOfTile();

};

#endif // TILE_H
