#include "gem.h"

int Gem::getPointValue()
{
    return this->pointValue;
}
void Gem::setPointValue(int pointValue)
{
    this->pointValue = pointValue;
}

void Gem::remove()
{
    (this->scene)->removeItem(this);
}
