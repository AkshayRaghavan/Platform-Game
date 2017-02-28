#ifndef SCORECOMPONENT_H
#define SCORECOMPONENT_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include<QDebug>
#include <string>

class ScoreComponent : public QGraphicsTextItem
{
public:
    const int scoreDisplayDiffX;
    const int scoreDisplayDiffY;
    ScoreComponent(qreal , qreal ,int , int , QColor , QFont);
    void update(int new_score);
};

#endif // SCORE_H
