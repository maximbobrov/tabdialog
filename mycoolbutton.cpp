#include "mycoolbutton.h"
#include <QGraphicsEffect>
#include <QStyle>

myCoolButton::myCoolButton(const QString &text, QWidget *parent):QPushButton(text, parent)
{
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(10); //Adjust accordingly
    effect->setOffset(0,2); //Adjust accordingly

    this->setGraphicsEffect(effect);

    this->setIcon(QIcon(":/images/blank.png"));
}

void myCoolButton::activate()
{

  QString style =  QString("QPushButton { \
            color: #eff0f1;\
            background-color: #3daee9;\
            border-width: 0px;\
            border-color: #76797C;\
            border-style: solid;\
            padding: 10px;\
            border-radius: 3px;\
            outline: none;\
           font:bold;\
           font-size: 12px;\
           font-family: \"Arial\";\
           text-align:left;\
        }");
    this->setStyleSheet(style);
    //QStyle *style=this->style();
    //style->se
    //this->setStyle();
    //this->style().

   // this->setChecked(true);
}

void myCoolButton::deactivate()
{

    QString style =  QString("QPushButton { \
              color: #eff0f1;\
              background-color: #663699\
              border-width: 0px;\
              border-color: #76797C;\
              border-style: solid;\
              padding: 10px;\
              border-radius: 3px;\
              outline: none;\
             font:bold;\
             font-size: 12px;\
             font-family: \"Arial\";\
             text-align:left;\
          }");
    this->setStyleSheet(style);
   //   this->setChecked(false);
}
