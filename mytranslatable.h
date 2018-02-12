#ifndef MYTRANSLATABLE_H
#define MYTRANSLATABLE_H

#include <QObject>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
class myTranslatable : public QObject
{
    Q_OBJECT
public:
    explicit myTranslatable(QObject *parent = 0);

   // configGroup;// = new QGroupBox(tr("UI Language"));
   // langLabel;// = new QLabel(tr("Set:"));


signals:

public slots:
    void retranslate();
};

#endif // MYTRANSLATABLE_H
