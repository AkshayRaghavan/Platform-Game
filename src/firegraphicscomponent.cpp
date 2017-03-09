#include "firegraphicscomponent.h"

FireGraphicsComponent::FireGraphicsComponent(QGraphicsScene* scene , QPixmap* pix_map , int images_total_count, qreal x_coordinate , qreal y_coordinate)
{
    isDangerous = true;
    pixMapArray = pix_map;
    imagesTotalCount = images_total_count;
    graphicsCounter = 0;
    this->setPos(x_coordinate,y_coordinate);
    this->setPixmap(pixMapArray[0]);
}

FireGraphicsComponent::~FireGraphicsComponent()
{
    for (int i = 0; i < imagesTotalCount; i++)
    {
        delete (&(pixMapArray[i]));
    }
}
void FireGraphicsComponent::update(GameObject &obj)
{
    graphicsCounter++;
    graphicsCounter %= imagesTotalCount;
    this->setPixmap(pixMapArray[graphicsCounter]);
}

std::vector<qreal> FireGraphicsComponent::getSizePositionOfObject()
{
    QRectF obj = this->boundingRect();
    std::vector<qreal> ans(4);
    ans[0] = (this->x());
    ans[1] = (this->y());
    ans[2] = (obj.width());
    ans[3] = (obj.height());
    return ans;
}
