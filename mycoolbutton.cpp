#include "mycoolbutton.h"
#include <QGraphicsEffect>


myCoolButton::myCoolButton(const QString &text, QWidget *parent):QPushButton(text, parent)
{
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(10); //Adjust accordingly
    effect->setOffset(0,2); //Adjust accordingly

    this->setGraphicsEffect(effect);
}
