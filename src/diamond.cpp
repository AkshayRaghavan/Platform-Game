#include "diamond.h"


Diamond::Diamond(QGraphicsScene* scene_local , std::string image_location , int width , int height , qreal x_coordinate , qreal y_coordinate)
{

    scene = scene_local;
    QImage gem_picture(image_location.c_str());


    if(gem_picture.isNull())
    {
        qDebug() << "ERROR(diamond.cpp) : Failed To Load Image" << image_location.c_str() << endl;
        std::exit(EXIT_FAILURE);
    }
    pixMapImage = QPixmap::fromImage(gem_picture);
    pixMapImage = pixMapImage.scaled(QSize(width,height), Qt::KeepAspectRatio);
    this->setPos(x_coordinate , y_coordinate);
}

void Diamond::draw()
{
    this->setPixmap(this->pixMapImage);
    scene->addItem(this);
}






























