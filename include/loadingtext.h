#ifndef LOADINGTEXT_H
#define LOADINGTEXT_H

#include <QLabel>
#include <QObject>
#include "client.h"
#include "inputhandler.h"

class LoadingText : public QObject
{
    Q_OBJECT
    QLabel* loadingTextDisplay;
 public:
    LoadingText(Client* , QGraphicsScene* , InputHandler* , qreal , qreal);
};
#endif // LOADINGTEXT_H
