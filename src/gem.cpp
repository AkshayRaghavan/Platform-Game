#include "gem.h"

inline int Gem::getPointValue()
{
    return this->pointValue;
}
inline void Gem::setPointValue(int pointValue)
{
    this->pointValue = pointValue;
}

inline QGraphicsScene* Gem::getQGraphicsScene()
{
    return this->scene;
}
inline void Gem::setQGraphicsScene(QGraphicsScene* scene)
{
    this->scene = scene;
}

void Gem::remove(QGraphicsScene *scene)
{
    scene->removeItem(this);
}
