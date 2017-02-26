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
    ScoreComponent(qreal x_coordinate , qreal y_coordinate , int font_size , int score_display_diff_x , int score_display_diff_y);
    void update(int new_score);
};

#endif // SCORE_H
