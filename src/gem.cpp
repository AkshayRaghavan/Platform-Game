#include "gem.h"

int Gem::getPointValue()
{
    return pointValue;
}

void Gem::setPointValue(int score_of_gem)
{
   pointValue = score_of_gem;
}

void Gem::remove(QGraphicsScene* scene)
{
    scene->removeItem(this);
}
