#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QDebug>

class Button:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
private:
    QPixmap idlePixMap;
    QPixmap hoverPixMap;
public:
    // constructors
    Button(const char*  , const char*  , int  , int );
    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
};

#endif // BUTTON_H
