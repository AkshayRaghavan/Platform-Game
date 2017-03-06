#ifndef INITIALCHOICESERVERBUTTON_H
#define INITIALCHOICESERVERBUTTON_H


class InitialChoiceServerButton: public QPushButton
{
    Q_OBJECT
    int millisecondsPerFrame;
    QGraphicsScene* scene;
    InputHandler* view_global;
    QApplication* core;
    std::vector<QGraphicsProxyWidget*> proxyVector;
    int screenWidth;
    int screenHeight;
 public:
    InitialChoiceServerButton(QApplication* , QGraphicsScene* , InputHandler* , const char* , int, int screen_width, int screen_height);
    void setProxy(QGraphicsProxyWidget*);
public slots:
    void changeEvent();
};
#endif // INITIALCHOICESERVERBUTTON_H
