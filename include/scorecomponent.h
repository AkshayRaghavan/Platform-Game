#ifndef SCORECOMPONENT_H
#define SCORECOMPONENT_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include<QDebug>
#include <string>

/*!
 * \brief Class to Display the Score on top of Player
 */

class ScoreComponent : public QGraphicsTextItem
{
public:
    /*!
     * \brief X Coordinate of the Score Display
     */
    const int scoreDisplayDiffX;
    /*!
     * \brief Y Coordinate of the Score Display
     */
    const int scoreDisplayDiffY;
    /*!
     * \brief Function to get scoreDisplayDiffX
     * \return value of scoreDisplayDiffX
     */
    int getscoreDisplayDiffX();
    /*!
     * \brief Function to get scoreDisplayDiffY
     * \return value of scoreDisplayDiffY
     */
    int getscoreDisplayDiffY();
    /*!
     * \brief Contructor
     * \param scene The scene where to add the score component
     * \param x_coordinate the position of x coordinate
     * \param y_coordinate the position of y coordinate
     * \param score_display_diff_x Difference in player and Score position in X
     * \param score_display_diff_y Difference in player and Score position in Y
     * \param text_color Color of the ScoreComponent
     * \param text_font Font of the ScoreComponent
     */
    ScoreComponent(QGraphicsScene* scene , qreal x_coordinate, qreal y_coordinate,
                   int score_display_diff_x, int score_display_diff_y,
                   QColor text_color,
                   QFont text_font);
    /*!
     * \brief To Update ScoreComponent
     * \param new_score The new score
     */
    void update(int new_score);
};

#endif // SCORE_H
