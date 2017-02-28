
#include "exitbutton.h"

ExitButton::ExitButton(const char* button_text)
{
    this->setGeometry(QRect(50,50,120,120));
    this->setText(button_text);
    QObject::connect(this, SIGNAL(clicked()), QCoreApplication::instance(), SLOT(quit()));
}
