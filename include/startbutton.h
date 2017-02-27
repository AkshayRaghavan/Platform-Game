#ifndef STARTBUTTON_H
#define STARTBUTTON_H
#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include <QEvent>
#include <QDebug>
#include "readinput.h"
#include "gamestate.h"
#include "gameobject.h"
#include "inputhandler.h"
#include <QDesktopWidget>
#include <startbutton.h>
#include<QGraphicsScene>
#include<QGraphicsProxyWidget>
#include <QPushButton>
#include <QDebug>
#include <QGraphicsScene>
class StartButton: public QPushButton
{
    Q_OBJECT
    QGraphicsScene* scene;
    QGraphicsView* view_global;
 public:
    StartButton(QGraphicsScene* scene_local,QGraphicsView* view_local,const char* button_text);
public slots:
    void changeEvent();
};
#endif // STARTBUTTON_H
