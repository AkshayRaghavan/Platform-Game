#include "scorecomponent.h"

ScoreComponent::ScoreComponent(QGraphicsScene* scene , qreal x_coordinate, qreal y_coordinate,
                               int score_display_diff_x, int score_display_diff_y,
                               QColor text_color,
                               QFont text_font ):
    scoreDisplayDiffX(score_display_diff_x) , scoreDisplayDiffY(score_display_diff_y)
{
      this->setPlainText("0");
      this->setFont(text_font);                          //QFont("Helvetica" , font_size)
      this->setDefaultTextColor(text_color);    //QColor(51, 51, 255)
      this->setPos(x_coordinate + score_display_diff_x,y_coordinate + score_display_diff_y);
      scene->addItem(this);
}

int ScoreComponent::getscoreDisplayDiffX()
{
    return scoreDisplayDiffX;
}

int ScoreComponent::getscoreDisplayDiffY()
{
    return scoreDisplayDiffY;
}

void ScoreComponent::update(int new_score)
{
    this->setPlainText(std::to_string(new_score).c_str());
}
