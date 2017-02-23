#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include <QPen>
#include <QGraphicsScene>

class Tile : public QGraphicsRectItem
{
private:
    bool isObstacle; //if obs present
    int left;
    int top;
    int width;
    int height;
    QGraphicsRectItem* r;
public:
    Tile(QGraphicsScene* scene , int left , int top , int width , int height , bool isObstacle);
    QGraphicsRectItem* getR();
    bool getIsObstacle();
};

#endif // TILE_H
