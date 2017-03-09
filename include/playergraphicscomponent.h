#ifndef PLAYERGRAPHICSCOMPONENT_H
#define PLAYERGRAPHICSCOMPONENT_H

#include "graphicscomponent.h"
#include "enumerator.h"
#include "state.h"
#include "jumpingstate.h"
#include "gameobject.h"
#include <QGraphicsScene>
#include<QPixmap>
#include<QDebug>
#include<vector>
#include <string>
#include <QApplication>

#define NO_Of_GRAPHICS_STATES 8


/*!
 * \brief The class for the graphics of the game objects
 * Used as virtual functions
 * And deriving QGraphicsPixmapItem for image of object
 */

class PlayerGraphicsComponent : public GraphicsComponent
{
private:
    /*!
     * \brief QApplication for processEvents
     */
    QApplication * app;

    /*!
     * \brief matrix to contain pixmaps of all the images of a player (walk , jump , dead , idle) <right , left for each>
     */
    std::vector<QPixmap*> pixMapMatrix;

    /*!
     * \brief Array for saving total images in a graphic state
     */
    std::vector<int> imagesTotalCount;

    /*!
     * \brief Array for telling which image of each state to be displayed next
     */
    std::vector<int> graphicsCounter;

    /*!
     * \brief to tell which picture to display next
     * \param index row in the pixmap matrix
     * \param obj default parameter for dead picture
     * \return index of picture to be displayed
     */
    int updateGraphicsCounter(int index , GameObject * obj = NULL);

    /*!
     * \brief used in constructor for images
     * \param images_total_count total images of a state
     * \param image_location image path directory
     * \param array_of_pixmaps array of state images
     * \param image_width image width
     * \param image_height  image height
     */
    void initializePixMaps(int images_total_count , std::string image_location ,  QPixmap* array_of_pixmaps , const int image_width , const int image_height);

public:
    /*!
     * \brief get left top coordinate and width and height of rectangle
     * \return  vector of image characteristics
     */
    std::vector<qreal> getSizePositionOfObject();

    /*!
     * \brief constructor for all the images of player and monster
     * \param scene add items to screen
     * \param images_location substring of the images location path
     * \param images_total_count vector of total images for the different states
     * \param image_width width of all images
     * \param image_height height of all images
     * \param x_coordinate x position of image
     * \param y_coordinate y position of image
     * \param is_dangerous differentiate player and monster
     * \param a Qapplication for processEvents
     */
    PlayerGraphicsComponent(QGraphicsScene* scene , std::string images_location , std::vector<int> &images_total_count, int image_width , int image_height , qreal x_coordinate , qreal y_coordinate , bool is_dangerous, QApplication * a);

    /*!
     * \brief destructor
     */
    ~PlayerGraphicsComponent();
    /*!
     * \brief in each game loop this function is called which changes the image based on graphicsCounter[]
     * \param obj player or zombie gameObject
     */
    void update(GameObject &obj);

    /*!
     * \brief setApp set the Qapplication
     * \param a Qapplication
     */
    void setApp(QApplication * a);
};

#endif // PLAYERGRAPHICSCOMPONENT_H
