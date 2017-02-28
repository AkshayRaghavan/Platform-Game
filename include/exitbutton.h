#ifndef EXITBUTTON_H
#define EXITBUTTON_H

#include <QCoreApplication>
#include <QDebug>
#include <QPushButton>

class ExitButton: public QPushButton
{
    Q_OBJECT
 public:
    ExitButton(const char*);
};
#endif // EXITBUTTON_H
