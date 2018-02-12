#ifndef MYCOOLBUTTON_H
#define MYCOOLBUTTON_H

#include <QObject>
#include <QPushButton>

class myCoolButton : public QPushButton
{
    Q_OBJECT
public:
       myCoolButton(const QString &text, QWidget *parent = Q_NULLPTR);

};

#endif // MYCOOLBUTON_H
