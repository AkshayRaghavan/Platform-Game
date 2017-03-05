#include "loadingtext.h"

LoadingText::LoadingText(Client* game_client, QGraphicsScene* scene, InputHandler* view , qreal position_x , qreal position_y)
{
    loadingTextDisplay = new QLabel("Contacting Server .....");
    loadingTextDisplay->setAttribute(Qt::WA_TranslucentBackground);
    loadingTextDisplay->move(position_x , position_y);
    loadingTextDisplay->setFixedWidth(500);
    QGraphicsProxyWidget* proxy_widget = scene->addWidget(loadingTextDisplay);

    if(QObject::connect(game_client, SIGNAL(textChanged(QString)), this->loadingTextDisplay, SLOT(setText(QString))))
        qDebug() << "Success connect";
    else
    {
        qDebug() << "Failed To Connect";
        std::exit(EXIT_FAILURE);
    }
    view->setGameClient(game_client);
}
