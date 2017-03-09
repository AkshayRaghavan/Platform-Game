#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

class GameObject;
#include<QGraphicsPixmapItem>
#include<QObject>

/*!
 * \brief Component of a GameObject that handles the graphics
 * Handles how to display a game object, and updating the display based on the State
 */

class GraphicsComponent : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    /*!
     * \brief Specifies whether a player will be destroyed by the GameObject corresponding to the GraphicsComponent
     */
    bool isDangerous;
public:
    /*!
     * \brief Constructor
     */
    GraphicsComponent(){}

    /*!
     * \brief Destructor
     */
    ~GraphicsComponent() {}

    /*!
     * \brief Updates the graphics of the gameObject
     * \param gameObject the GameObject the GraphicsComponent belongs to
     */
    virtual void update(GameObject &gameObject) {}

    /*!
     * \brief Get whether the GameObject corresponding to the GraphicsComponent is dangerous
     * \return true, if a player will be destroyed by it, false, otherwise
     */
    bool getIsDangerous();

    /*!
     * \brief Get the size and position
     * \return
     */
    virtual std::vector<qreal> getSizePositionOfObject() = 0;
    virtual void setPosScorePointer( int , int ){}
};


#endif // GRAPHICSCOMPONENT_H
