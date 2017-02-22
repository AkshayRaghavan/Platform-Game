#include "gem.h"

int Gem::getPointValue()
{
    return this->pointValue;
}
void Gem::setPointValue(int pointValue)
{
    this->pointValue = pointValue;
}

QGraphicsScene* Gem::getQGraphicsScene()
{
    return this->scene;
}
void Gem::setQGraphicsScene(QGraphicsScene* scene)
{
    this->scene = scene;
}

void Gem::remove()
{
    (this->scene)->removeItem(this);
}
