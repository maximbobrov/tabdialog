#ifndef MYCOOLBUTTON_H
#define MYCOOLBUTTON_H

#include <QObject>
#include <QPushButton>

class myCoolButton : public QPushButton
{
    Q_OBJECT
public:
       myCoolButton(const QString &text, QWidget *parent = Q_NULLPTR);
       void activate();
       void activate1();
          void activate2();

       void deactivate();
       void deactivate1();

};

#endif // MYCOOLBUTON_H
