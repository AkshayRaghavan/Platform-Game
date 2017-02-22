#include "gemtype1.h"

GemType1::GemType1(std::string image_location , int scaling_factor)
{
    if(!this->pixMapImage.load((image_location).c_str()))
    {
        qDebug() << "ERROR(gemtype1.cpp) : Failed To Load Gem Image" << image_location.c_str() <<endl;
        std::exit(EXIT_FAILURE);
    }
    this->pixMapImage = this->pixMapImage.scaled(QSize(scaling_factor,scaling_factor));
}
void GemType1::draw()
{
    this->setPixmap(this->pixMapImage);
    (getQGraphicsScene())->addItem(this);
}
















