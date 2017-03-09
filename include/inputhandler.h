#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QCoreApplication>
#include <QEvent>
#include <QKeyEvent>
#include <vector>
#include "inputcomponent.h"
#include "gamestate.h"
#include "keys.h"
#include "client.h"

class Client;

/*!
 * \brief View that also handles key press and key release events
 * Used to show the scene, and to receive key press and key release events and pass it where needed
 */

class InputHandler : public QGraphicsView
{
private:
    /*!
     * \brief Stores the state of the game
     */
    GameState *gameState;

    /*!
     * \brief Stores a pointer to the Client object of the client
     */
    Client * clientPtr;
public:
    /*!
     * \brief Constructor
     * \param game_state the state of the current game
     */
    InputHandler(GameState *game_state);

    /*!
     * \brief Store the client object of the game when running in the client
     * \param client_input Client object to be stored
     */
    void setGameClient(Client *client_input);

    /*!
     * \brief Set the state of the game here
     * \param game_state the state of the game
     */
    void setGameState(GameState *game_state);

    /*!
     * \brief Receive key press events and process it
     * \param event the key press event received
     */
    void keyPressEvent(QKeyEvent *event);

    /*!
     * \brief Receive key release events and process it
     * \param event the key release event
     */
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // INPUTHANDLER_H
