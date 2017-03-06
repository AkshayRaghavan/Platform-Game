#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QLineEdit>
#include <QUrl>
#include <QObject>
#include <QHBoxLayout>
#include "inputhandler.h"
#include "client.h"
class InputBox : public QObject
{
    Q_OBJECT
    QFrame* f;
    QHBoxLayout* flayout;
    Client * client;
public:
    QLineEdit* lineEdit;
    InputBox(QFrame* , QHBoxLayout* , const char* , Client*);
private slots:
    void pingServer();
};
#endif // INPUTBOX_H
