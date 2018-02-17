#include "mycoolbutton.h"
#include <QGraphicsEffect>
#include <QStyle>

myCoolButton::myCoolButton(const QString &text, QWidget *parent):QPushButton(text, parent)
{
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(10); //Adjust accordingly
    effect->setOffset(0,2); //Adjust accordingly

    this->setGraphicsEffect(effect);

   // this->setIcon(QIcon(":/images/blank.png"));
}

void myCoolButton::activate()
{

  QString style =  QString("QPushButton { \
            color: #222222;\
            background-color: #a5fdf4;\
            border-width: 3px;\
            border-color: white;\
            border-style: solid;\
            padding: 10px;\
            border-radius: 10px;\
            outline: none;\
           font:bold;\
           font-size: 14px;\
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
void myCoolButton::activate1()
{

    QString style =  QString("QPushButton { \
              color: #666666;\
              background-color: #ffffff;\
              border-width: 3px;\
              border-color: aquamarine;\
              border-style: solid;\
              padding: 10px;\
              border-radius: 10px;\
              outline: none;\
             font:bold;\
             font-size: 14px;\
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
void myCoolButton::activate2()
{

    QString style =  QString("QPushButton { \
              color: #666666;\
              background-color: #ffffff;\
              border-width: 3px;\
              border-color: mediumspringgreen ;\
              border-style: solid;\
              padding: 10px;\
              border-radius: 10px;\
              outline: none;\
             font:bold;\
             font-size: 14px;\
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
              color: #888888;\
              background-color: #663699\
              border-width: 0px;\
              border-color: #76797C;\
              border-style: solid;\
              padding: 10px;\
              border-radius: 3px;\
              outline: none;\
             font:bold;\
             font-size: 14px;\
             font-family: \"Arial\";\
             text-align:left;\
          }");
    this->setStyleSheet(style);
   //   this->setChecked(false);
}
