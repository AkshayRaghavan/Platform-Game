#include "firegraphicscomponent.h"

FireGraphicsComponent::FireGraphicsComponent(QGraphicsScene* scene_formal_arg ,  std::string images_location , int images_total_count, int image_width , int image_height , qreal x_coordinate , qreal y_coordinate):
{
    isDangerous = true;
    scene = scene_formal_arg;
    for(int i = 0; i < images_total_count; i++)
    {
        if(!array_of_pixmaps[i].load((image_location + std::to_string(i+1) +").png").c_str()))
        {
            qDebug() << "ERROR(playergraphicscomponent.cpp) : Failed To Load Image" << image_location.c_str() << (i+1) << ").png" <<endl;
            std::exit(EXIT_FAILURE);
        }
        pixMapArray[i] = pixMapArray[i].scaled(QSize(image_width,image_height),  Qt::KeepAspectRatio);
    }
    imagesTotalCount = images_total_count;
    graphicsCounter = 0;
    this->setPixmap(this->pixMapArray[0]);
    this->setPos(x_coordinate,y_coordinate);
    scene->addItem(this);
}

void FireGraphicsComponent::update()
{
    graphicsCounter++;
    graphicsCounter %= imagesTotalCount;
    this->setPixmap(pixMapArray[graphicsCounter]);
}
