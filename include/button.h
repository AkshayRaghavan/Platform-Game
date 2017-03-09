#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QDebug>

/*!
 * \brief All the buttons displayed in Main Menu
 */

class Button:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
private:
    /*!
     * \brief PixMap to be displayed when Mouse is away from button
     */
    QPixmap idlePixMap;
    /*!
     * \brief PixMap to be displayed when Mouse is on the button
     */
    QPixmap hoverPixMap;
public:
    // constructors
    /*!
     * \brief The Constructor for button class
     * \param idle_image_path file path containing image for idlePixMap
     * \param hover_image_path file path containing image for hoverPixMap
     * \param screen_height Height of the Screen
     * \param screen_width Width of the Screen
     */
    Button(const char* idle_image_path , const char* hover_image_path , int screen_height , int screen_width);
    // public methods (events)
    /*!
     * \brief Function called when button gets clicked
     * \param event The Event received
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /*!
     * \brief Function called when mouse cursor touches the button
     * \param event The Event received
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    /*!
     * \brief Function called when mouse cursor leaves the button
     * \param event The Event received
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    /*!
     * \brief Signal to notify if button is clicked
     */
    void clicked();
};

#endif // BUTTON_H
