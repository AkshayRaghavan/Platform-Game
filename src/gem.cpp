#include "gem.h"

int Gem::getPointValue()
{
    return pointValue;
}

bool Gem::getIsOnScreen()
{
    return isOnScreen;
}

void Gem::setIsOnScreen(bool is_on_screen)
{
    isOnScreen = is_on_screen;
}

bool Gem::getRemovedFromScreen()
{
    return removedFromScreen;
}

void Gem::setRemovedFromScreen(bool removed_from_screen)
{
    removedFromScreen = removed_from_screen;
}


void Gem::setPointValue(int score_of_gem)
{
   pointValue = score_of_gem;
}

void Gem::remove(QGraphicsScene* scene)
{
    scene->removeItem(this);
}
