#ifndef TILE_H
#define TILE_H

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QGraphicsScene>
#define screenHeight 600
#define screenWidth 1000
#define width_of_tile 20
#define height_of_tile 20
#define rowTileMatrix screenHeight/height_of_tile + 1
#define columnTileMatrix screenWidth/width_of_tile + 1


class tile : public QMainWindow
{
public:
    QGraphicsRectItem *r;
    QGraphicsScene * scene;
    int left,top,width,height;
    bool isObstacle,ispoint;
    tile(QGraphicsScene* scene ,int left , int top , int width , int height , bool isObstacle, bool ispoint);
    void change_point_type();
};

#endif // TILE_H
