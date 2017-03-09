#ifndef CHOICESERVERCLIENTSTART_H
#define CHOICESERVERCLIENTSTART_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QDebug>
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "server.h"
#include "client.h"
#include "inputhandler.h"
#include "button.h"

/*!
 * \brief The Choice between Server ClientStart class
 */

class ChoiceServerClientStart :public QObject
{
    Q_OBJECT
    /*!
     * \brief The Label to print messages
     */
    QLabel* label;
    /*!
     * \brief The Global Frame
     */
    QFrame* fGlobal;
    /*!
     * \brief Message of Client
     */
    QGraphicsTextItem* clientMessage;
    /*!
     * \brief Input URL
     */
    QLineEdit* inputURL;
    /*!
     * \brief Player Name
     */
    QLineEdit* name;

    /*!
     * \brief Scene
     */
    QGraphicsScene* scene;
    /*!
     * \brief View
     */
    InputHandler* view;
    /*!
     * \brief Milli Seconds Per Frame
     */
    int millisecondsPerFrame;
    /*!
     * \brief Screen Width
     */
    int screenWidth;
    /*!
     * \brief Screen Height
     */
    int screenHeight;
    /*!
     * \brief Client Object
     */
    Client* client;
    /*!
     * \brief Server Object
     */
    Server * server;
public:
    /*!
     * \brief Constructor
     * \param parent
     */
    ChoiceServerClientStart(QGraphicsScene* , InputHandler* , const char * , int , int , int , Client* , Server* , QLabel* ,QWidget *parent = NULL);
    /*!
     * \brief Destructor
     */
    ~ChoiceServerClientStart();
    /*!
     * \brief Display Start Menu
     */
    void displayStartMenu();
private slots:
    /*!
     * \brief Start the Client
     */
    void startClient();
    /*!
     * \brief Start the Server
     */
    void startServer();
    /*!
     * \brief Start Server Game Slot Button Click
     */
    void startServerGameSlotButtonClick();
    /*!
     * \brief Start Client Game Slot Button Click
     */
    void startClientGameSlotButtonClick();

};

#endif // CHOICESERVERCLIENTSTART_H
