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
#include <QLabel>
#include<QMovie>
class StartButton: public QPushButton
{
    Q_OBJECT
    QGraphicsScene* scene;
    InputHandler* view_global;
    QApplication* core;
    std::vector<QGraphicsProxyWidget*> proxyVector;
 public:
    StartButton(QApplication* a ,QGraphicsScene* scene_local,InputHandler* view_local,const char* button_text);
    void setProxy(QGraphicsProxyWidget*);
public slots:
    void changeEvent();
};
#endif // STARTBUTTON_H
