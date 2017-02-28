#include "diamond.h"


Diamond::Diamond(std::string image_location , int width , int height , qreal x_coordinate , qreal y_coordinate , int score_of_gem)
{
    setPointValue(score_of_gem);
    QImage gem_picture(image_location.c_str());

    if(gem_picture.isNull())
    {
        qDebug() << "ERROR(diamond.cpp) : Failed To Load Image" << image_location.c_str() << endl;
        std::exit(EXIT_FAILURE);
    }
    pixMapImage = QPixmap::fromImage(gem_picture);
    pixMapImage = pixMapImage.scaled(QSize(width,height), Qt::KeepAspectRatio);
    this->setPos(x_coordinate , y_coordinate);
    this->setPixmap(this->pixMapImage);
}

void Diamond::drawGem(QGraphicsScene* scene)
{
    scene->addItem(this);
}






























