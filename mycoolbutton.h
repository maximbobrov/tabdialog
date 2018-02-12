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
       void deactivate();

};

#endif // MYCOOLBUTON_H
