#include "diamond.h"


Diamond::Diamond(std::string image_location , int width , int height , qreal x_coordinate , qreal y_coordinate)
{
    QImage diamond_picture(image_location.c_str());
    if(diamond_picture.isNull())
    {
        qDebug() << "ERROR(diamond.cpp) : Failed To Load Gem Image" << image_location.c_str() <<endl;
        std::exit(EXIT_FAILURE);
    }
    pixMapImage = QPixmap::fromImage(diamond_picture);
    pixMapImage = pixMapImage.scaled(QSize(width,height));
    this->setPos(x_coordinate , y_coordinate);
    this->setPixmap(pixMapImage);
}

void Diamond::draw(QGraphicsScene* scene)
{
    scene->addItem(this);
}






























