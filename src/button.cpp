#include "button.h"
#include <QGraphicsTextItem>
#include <QBrush>

Button::Button(const char* idle_image_path , const char* hover_image_path , int screen_height , int screen_width)
{
    // draw the rect

    QImage * picture;
    picture = new QImage(idle_image_path);
    if(picture->isNull())
    {
        qDebug() << "ERROR(button.cpp) : Failed To Load Image" << idle_image_path;
        std::exit(EXIT_FAILURE);
    }
    idlePixMap = QPixmap::fromImage(*picture);
    if(idlePixMap.isNull())
    {
        qDebug() << "ERROR(button.cpp) : Failed To Create Pixmap of " << idle_image_path;
        std::exit(EXIT_FAILURE);
    }

    idlePixMap = idlePixMap.scaled(QSize(screen_width/5,screen_height/5),  Qt::KeepAspectRatio);

    picture = new QImage(hover_image_path);
    if(picture->isNull())
    {
        qDebug() << "ERROR(button.cpp) : Failed To Load Image" << hover_image_path;
        std::exit(EXIT_FAILURE);
    }
    hoverPixMap = QPixmap::fromImage(*picture);
    if(hoverPixMap.isNull())
    {
        qDebug() << "ERROR(button.cpp) : Failed To Create Pixmap of " << hover_image_path;
        std::exit(EXIT_FAILURE);
    }
    hoverPixMap = hoverPixMap.scaled(QSize(screen_width/5,screen_height/5),  Qt::KeepAspectRatio);

    this->setPixmap(idlePixMap);
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    this->setPixmap(hoverPixMap);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    this->setPixmap(idlePixMap);
}
