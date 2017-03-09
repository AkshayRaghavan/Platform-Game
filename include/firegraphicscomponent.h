#ifndef FIREGRAPHICSCOMPONENT_H
#define FIREGRAPHICSCOMPONENT_H

#include "graphicscomponent.h"
#include "gameobject.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsTextItem>
#include <QDebug>
#include <string>
#include <QApplication>
#include <vector>

/*!
 * \brief The Graphics for fire objects
 * This handles the drawing, placement, position and update of fire objects
 */

class FireGraphicsComponent : public GraphicsComponent
{
private:

    /*!
     * \brief A 2D array to contain pixmaps of all the images of a player
     * (walk , jump , dead , idle) <right , left for each>
     */
    QPixmap* pixMapArray;

    /*!
     * \brief imagesTotalCount total images in a graphic state
     */
    int imagesTotalCount;

    /*!
     * \brief graphicsCounter tells which image of each state to be displayed next
     */
    int graphicsCounter;

public:
    /*!
     * \brief Constructor
     * \param scene the scene where the fire is placed
     * \param pix_map Pixmap for the fire
     * \param images_total_count number of images to be looped over
     * \param x_coordinate x coordinate of the position
     * \param y_coordinate y coordinate of the position
     */
    FireGraphicsComponent(QGraphicsScene* scene , QPixmap* pix_map , int images_total_count, qreal x_coordinate , qreal y_coordinate);

    /*!
     * \brief Destructor
     */
    ~FireGraphicsComponent() {}


    /*!
     * \brief update Updates the image based on graphicsCounter
     * \param gameObject the GameObject of the fire
     */
    void update(GameObject &gameObject);

    /*!
     * \brief Gives the size and position of the GraphicsComponent of the GameObject
     * \return a vector of type qreal, with width, height, x coordinate, y coordinate filled in that order
     */
     std::vector<qreal> getSizePositionOfObject();

    QPixmap* pixmapPointer;
    QPoint* position;
   
    

};

#endif // FIREGRAPHICSCOMPONENT_H
