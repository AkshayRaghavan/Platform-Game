#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000/33);
    ReadInput readInput;
    GameState *gameState = readInput.createGameStateObject();
    connect(timer,SIGNAL(timeout()),gameState,SLOT(update()));
    return a.exec();
}
